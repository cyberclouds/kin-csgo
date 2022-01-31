#pragma once
#include <vector>
#include "../sdk/entity.h"

namespace game {
    struct usercmd_t {
        uintptr_t vt_pointer; // 0x00
        int32_t m_iCmdNumber; // 0x04
        int32_t m_iTickCount; // 0x08
        vec3_t m_vecViewAngles; // 0x0C
        vec3_t m_vecAimDirection; // 0x18
        float m_flForwardmove; // 0x24
        float m_flSidemove; // 0x28
        float m_flUpmove; // 0x2C
        int32_t m_iButtons; // 0x30
        uint8_t m_bImpulse; // 0x34
        uint8_t pad1[ 3 ];
        int32_t m_iWeaponSelect; // 0x38
        int32_t m_iWeaponSubtype; // 0x3C
        int32_t m_iRandomSeed; // 0x40
        int16_t m_siMouseDx; // 0x44
        int16_t m_siMouseDy; // 0x46
        bool m_bHasBeenPredicted; // 0x48
        uint8_t pad2[ 27 ];
    }; //0x64

    struct verified_usercmd_t {
        usercmd_t m_Command;
        uint32_t m_Crc;
    };
    struct globals_t {
        float realtime;
        int framecount;
        float absoluteframetime;
        float absoluteframetimesttdev;
        float curtime;
        float frametime;
        int max_clients;
        int tickcount;
        float interval_per_tick;
        float interpolation_amount;
    };
}

namespace kin {
    class context {
        uint32_t _engine_pointer;
        bool _is_connected;
    public:
        context( ) {
            _engine_pointer = mem->read< uint32_t >( mem->engine_base + game::signatures::dwClientState );
            _is_connected = false;
            player_data.reserve( 64 );
        }

        std::vector< game::entity_t::player_data_t > player_data;
        game::entity_t::player_data_t local;
        game::globals_t globals;

        bool is_connected( ) {
            return _is_connected;
        }

        auto get_engine_pointer( ) {
            return _engine_pointer;
        }

        void in_game_check( ) {
            _is_connected = mem->read< int >( _engine_pointer + game::signatures::dwClientState_State ) == 6;
        }

        static void get_global_vars( game::globals_t& g ) {
            g = mem->read< game::globals_t >( mem->engine_base + game::signatures::dwGlobalVars );
        }

        static void send_packet( const bool status ) {
            const byte val = status ? 1 : 0;
            mem->write< byte >( mem->engine_base + game::signatures::dwbSendPackets, val );
        }

        game::vec3_t view_angles( ) {
            return mem->read< game::vec3_t >( _engine_pointer + game::signatures::dwClientState_ViewAngles );
        }

        void set_view_angles( game::vec3_t v ) {
            mem->write< game::vec3_t >( _engine_pointer + game::signatures::dwClientState_ViewAngles, v );
        }

        bool can_shoot( ) const {
            return !( local.m_flNextPrimaryAttack > local.m_nTickBase * globals.interval_per_tick );
        }

        static game::usercmd_t fix_cmd( game::usercmd_t cur, const game::usercmd_t old ) {
            cur.m_vecViewAngles = old.m_vecViewAngles;
            cur.m_vecAimDirection = old.m_vecAimDirection;
            cur.m_flForwardmove = old.m_flForwardmove;
            cur.m_flSidemove = old.m_flSidemove;
            cur.m_flUpmove = old.m_flUpmove;
            cur.m_iButtons = old.m_iButtons;
            cur.m_siMouseDx = old.m_siMouseDx;
            cur.m_siMouseDy = old.m_siMouseDy;

            return cur;
        }

        static void set_tick_count( const int tick ) {
            mem->write< int >( mem->engine_base + game::signatures::dwGlobalVars + 0x1C, tick );
        }
    };
}

extern std::unique_ptr< kin::context > ctx;
