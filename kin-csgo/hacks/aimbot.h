#pragma once
#include "../kin.h"

namespace kin::h {
    class aimbot {
        int _best_target = -1;

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
            if ( !cfg->aimbot_enabled || !ctx->is_connected( ) || !ctx->can_shoot( ) || !GetAsyncKeyState( VK_LBUTTON ) || _best_target == -1 )
                return;

            const auto e = ents->get_player_data_by_index( _best_target );

            auto aim_ang = calc_angle( ctx->local.m_vecViewOffset + ctx->local.m_vecOrigin, bone_position( e, 8 ) );
            aim_ang -= ctx->local.m_aimPunchAngle * 2.f;

            aim_ang.normalize_angles( );

            auto delta = aim_ang - ctx->view_angles( );
            delta.normalize_angles( );
            delta.clamp( );

            auto move_ang = ctx->view_angles( ) + delta * 0.5;
            move_ang.normalize_angles( );
            move_ang.clamp( );

            ctx->set_view_angles( aim_ang );

        }

        void update( ) {
            if ( !cfg->aimbot_enabled || !ctx->is_connected( ) )
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

                const auto head_pos = bone_position( e, 8 );
                const auto fov_distance = get_fov( ctx->view_angles( ) - ( ctx->local.m_aimPunchAngle * 2.0f ), ctx->local.m_vecViewOffset + ctx->local.m_vecOrigin, head_pos );

                if ( best_fov > fov_distance ) {
                    best_fov = fov_distance;
                    _best_target = e.index;
                }
            }
        }
    };
}

extern std::unique_ptr< kin::h::aimbot > aim;
