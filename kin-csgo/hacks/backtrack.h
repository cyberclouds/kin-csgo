#pragma once
#include "../sdk.h"
#include <future>

#define PI 3.14159265358979323846f

namespace kin::h {
    class backtrack {
        struct backtrack_data_t {
            float simtime;
            game::vec3_t hitbox_pos;
        };
        backtrack_data_t _backtrack_positions[ 64 ][ 12 ] = { 0.0f, game::vec3_t( 0.f, 0.f, 0.f ) };
        int _best_target = -1;
        int _max_backtrack_ms = 200; // TODO: config

        static int time_to_ticks( float time ) {
            return static_cast< int >( 0.5f + time / ctx->globals.interval_per_tick );
        }

        bool is_valid_tick( const int tick ) const {
            const auto delta = ctx->globals.tickcount - tick;
            const auto delta_time = delta * ctx->globals.interval_per_tick;
            const auto max = static_cast< float >( _max_backtrack_ms ) / static_cast< float >( 1000 );
            return fabs( delta_time ) <= max;
        }

        static void make_vector( game::vec3_t angle, game::vec3_t& vector ) {
            const auto pitch = static_cast< float >( angle[ 0 ] * PI / 180 );
            const auto yaw = static_cast< float >( angle[ 1 ] * PI / 180 );
            const auto tmp = static_cast< float >( cos( pitch ) );
            vector[ 0 ] = static_cast< float >( -tmp * -cos( yaw ) );
            vector[ 1 ] = static_cast< float >( sin( yaw ) * tmp );
            vector[ 2 ] = static_cast< float >( -sin( pitch ) );
        }

        static game::vec3_t calc_angle( game::vec3_t src, game::vec3_t dst ) {
            game::vec3_t q_angles;
            auto delta = game::vec3_t( ( src[ 0 ] - dst[ 0 ] ), ( src[ 1 ] - dst[ 1 ] ), ( src[ 2 ] - dst[ 2 ] ) );
            const double hyp = sqrtf( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );
            q_angles[ 0 ] = static_cast< float >( atan( delta[ 2 ] / hyp ) * ( 180.0 / PI ) );
            q_angles[ 1 ] = static_cast< float >( atan( delta[ 1 ] / delta[ 0 ] ) * ( 180.0 / PI ) );
            q_angles[ 2 ] = 0.f;
            if ( delta[ 0 ] >= 0.f )
                q_angles[ 1 ] += 180.f;

            return q_angles;
        }

        static float get_fov( game::vec3_t angles, game::vec3_t src, game::vec3_t dst ) {
            game::vec3_t aim;

            auto ang = calc_angle( src, dst );
            make_vector( angles, aim );
            make_vector( ang, ang );

            const auto mag_s = sqrt( ( aim[ 0 ] * aim[ 0 ] ) + ( aim[ 1 ] * aim[ 1 ] ) + ( aim[ 2 ] * aim[ 2 ] ) );
            const auto mag_d = sqrt( ( aim[ 0 ] * aim[ 0 ] ) + ( aim[ 1 ] * aim[ 1 ] ) + ( aim[ 2 ] * aim[ 2 ] ) );
            const auto u_dot_v = aim[ 0 ] * ang[ 0 ] + aim[ 1 ] * ang[ 1 ] + aim[ 2 ] * ang[ 2 ];

            double fov = acos( u_dot_v / ( mag_s * mag_d ) ) * ( 180.f / PI );

            fov *= 1.4;
            const auto x_dist = abs( src[ 0 ] - dst[ 0 ] );
            const auto y_dist = abs( src[ 1 ] - dst[ 1 ] );
            auto distance = sqrt( ( x_dist * x_dist ) + ( y_dist * y_dist ) );

            distance /= 650.f;

            if ( distance < 0.7f )
                distance = 0.7f;

            if ( distance > 6.5 )
                distance = 6.5;

            fov *= distance;

            return static_cast< float >( fov );
        }

        auto bone_position( const game::entity_t::player_data_t e, const int bone ) {
            game::vec3_t out;
            auto m = mem->read< game::matrix3x4_t >( e.m_dwBoneMatrix + 0x30 * bone );
            out.x = m[ 0 ][ 3 ];
            out.y = m[ 1 ][ 3 ];
            out.z = m[ 2 ][ 3 ];
            return out;
        }

    public:
        void work( ) {
            if ( !cfg->backtrack_enabled || !ctx->is_connected( ) || !ctx->can_shoot( ) )
                return;

            std::shared_future< float > future_simtime = std::async( std::launch::async, &backtrack::best_simtime, this );

            const auto cur_seq_num = mem->read< int >( ctx->get_engine_pointer( ) + game::signatures::clientstate_last_outgoing_command ) + 1;

            ctx->send_packet( false );

            const auto input = mem->read< game::input_t >( mem->client_base + game::signatures::dwInput );

            const auto ptr_usercmd = input.m_pCommands + ( cur_seq_num % 150 ) * sizeof( game::usercmd_t );
            const auto ptr_verified_usercmd = input.m_pVerifiedCommands + ( cur_seq_num % 150 ) * sizeof( game::verified_usercmd_t );

            const auto ptr_old_usercmd = input.m_pCommands + ( ( cur_seq_num - 1 ) % 150 ) * sizeof( game::usercmd_t );

            while ( mem->read< int32_t >( ptr_usercmd + 0x4 ) < cur_seq_num ) {
                std::this_thread::yield( );
            }

            auto old_usercmd = mem->read< game::usercmd_t >( ptr_old_usercmd );
            auto usercmd = mem->read< game::usercmd_t >( ptr_usercmd );

            usercmd = ctx->fix_cmd( usercmd, old_usercmd );

            while ( future_simtime.wait_for( std::chrono::milliseconds( 0 ) ) == std::future_status::timeout ) { }

            if ( future_simtime.get( ) == -1 ) {
                ctx->send_packet( true );
                return;
            }

            usercmd.m_iButtons |= game::IN_ATTACK;
            usercmd.m_iTickCount = time_to_ticks( future_simtime.get( ) );

            mem->write< game::usercmd_t >( ptr_usercmd, usercmd );
            mem->write< game::usercmd_t >( ptr_verified_usercmd, usercmd );

            ctx->send_packet( true );
        }

        float best_simtime( ) {
            if ( _best_target == -1 )
                return -1;

            auto temp = FLT_MAX;
            float best = -1;

            for ( auto t = 0; t < 12; ++t ) {
                if ( _max_backtrack_ms > 0 && !is_valid_tick( time_to_ticks( _backtrack_positions[ _best_target ][ t ].simtime ) ) )
                    continue;

                const auto fov_distance = get_fov( ctx->view_angles( ) + ( ctx->local.m_aimPunchAngle * 2.0f ), ctx->local.m_vecViewOffset + ctx->local.m_vecOrigin, _backtrack_positions[ _best_target ][ t ].hitbox_pos );

                if ( temp > fov_distance && _backtrack_positions[ _best_target ][ t ].simtime > ctx->local.m_flSimulationTime - 1 ) {
                    temp = fov_distance;
                    best = _backtrack_positions[ _best_target ][ t ].simtime;
                }
            }

            return best;
        }

        void update( ) {
            if ( !cfg->backtrack_enabled || !ctx->is_connected( ) )
                return;

            _best_target = -1;

            auto best_fov = FLT_MAX;
            if ( ctx->local.m_iHealth < 1 )
                return;

            for ( auto e : ctx->player_data ) {
                if ( e.index == ctx->local.index )
                    continue;

                if ( e.m_bDormant )
                    continue;

                if ( e.m_iTeamNum == ctx->local.m_iTeamNum )
                    continue;

                if ( e.m_iHealth < 1 )
                    continue;

                const auto simtime = e.m_flSimulationTime;
                const auto head_pos = bone_position( e, 8 );

                _backtrack_positions[ e.index ][ ctx->globals.tickcount % 13 ] = backtrack_data_t{ simtime, head_pos };
                const auto fov_distance = get_fov( ctx->view_angles( ) - ( ctx->local.m_aimPunchAngle * 2.0f ), ctx->local.m_vecViewOffset + ctx->local.m_vecOrigin, head_pos );

                if ( best_fov > fov_distance ) {
                    best_fov = fov_distance;
                    _best_target = e.index;
                }
            }
        }
    };
}

extern std::unique_ptr< kin::h::backtrack > bt;
