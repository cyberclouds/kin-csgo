#pragma once
#include "vec3.h"
#include "../kin/mem.h"
#include "offsets.h"
#include "matrix3x4.h"

namespace game {
    class entity_t {
    public:
        std::uintptr_t address;
        int idx;

        entity_t( ) {
            address = -1;
            idx = -1;
        }

        entity_t( const std::uintptr_t ptr ) {
            address = ptr;
            idx = mem->read< int >( ptr + 0x64 );
        }

        entity_t( const std::uintptr_t ptr, const int i ) {
            address = ptr;
            idx = i;
        }

        struct player_data_t {
            uint32_t address;
            char pad_0x01[ 0x64 - sizeof( uint32_t ) ];
            int index;
            char pad_0xED[ netvars::m_clrRender - 0x64 - sizeof( int ) ];
            uint32_t m_clrRender;
            char pad_0xF4[ signatures::m_bDormant - netvars::m_clrRender - sizeof( uint32_t ) ]; //121
            bool m_bDormant;
            char pad_0x100[ netvars::m_iTeamNum - signatures::m_bDormant - sizeof( bool ) ];
            int m_iTeamNum;
            char pad_0x104[ netvars::m_iHealth - netvars::m_iTeamNum - sizeof( int ) ];
            int m_iHealth;
            int m_fFlags;
            vec3_t m_vecViewOffset;
            vec3_t m_vecVelocity;
            char pad_0x14C[ netvars::m_vecOrigin - netvars::m_vecVelocity - sizeof( vec3_t ) ];
            vec3_t m_vecOrigin;
            char pad_0x25C[ netvars::m_MoveType - netvars::m_vecOrigin - sizeof( vec3_t ) ];
            unsigned char m_MoveType;
            char pad_0x268[ netvars::m_lifeState - netvars::m_MoveType - sizeof( unsigned char ) ];
            unsigned char m_lifeState;
            char pad_0x444[ netvars::m_flSimulationTime - netvars::m_lifeState - sizeof( unsigned char ) ];
            float m_flSimulationTime;
            char pad_0x980[ netvars::m_bSpotted - netvars::m_flSimulationTime - sizeof( float ) ];
            bool m_bSpotted;
            char pad_0x1A84[ netvars::m_bSpottedByMask - netvars::m_bSpotted - sizeof( bool ) ];
            bool m_bSpottedByMask;
            char pad_0x2690[ netvars::m_dwBoneMatrix - netvars::m_bSpottedByMask - sizeof( bool ) ];
            uintptr_t m_dwBoneMatrix;
            char pad_0x2DF8[ netvars::m_flNextAttack - netvars::m_dwBoneMatrix - sizeof( uintptr_t ) ];
            float m_flNextAttack;
            char pad_0x2EF8[ netvars::m_hMyWeapons - netvars::m_flNextAttack - sizeof( float ) ];
            int m_hMyWeapons;
            char pad_0x2FAA[ netvars::m_hActiveWeapon - netvars::m_hMyWeapons - sizeof( int ) ];
            int m_hActiveWeapon;
            char pad_0x2FBC[ netvars::m_iItemDefinitionIndex - netvars::m_hActiveWeapon - sizeof( int ) ];
            short m_iItemDefinitionIndex;
            char pad_0x2FC8[ netvars::m_Local - netvars::m_iItemDefinitionIndex - sizeof( short ) ];
            uint32_t m_Local;
            char pad_0x302C[ netvars::m_iAccountID - netvars::m_Local - sizeof( uint32_t ) ];
            int m_iAccountID;
            char pad_0x3038[ netvars::m_aimPunchAngle - netvars::m_iAccountID - sizeof( int ) ];
            vec3_t m_aimPunchAngle;
            char pad_0x31E8[ netvars::m_iFOV - netvars::m_aimPunchAngle - sizeof( vec3_t ) ];
            int m_iFOV;
            char pad_0x3248[ netvars::m_flNextPrimaryAttack - netvars::m_iFOV - sizeof( int ) ];
            float m_flNextPrimaryAttack;
            char pad_0x3254[ netvars::m_iState - netvars::m_flNextPrimaryAttack - sizeof( float ) ];
            int m_iState;
            char pad_0x3295[ netvars::m_iClip1 - netvars::m_iState - sizeof( int ) ];
            int m_iClip1;
            char pad_0x3320[ netvars::m_hViewModel - netvars::m_iClip1 - sizeof( int ) ];
            int m_hViewModel;
            char pad_0x338C[ netvars::m_iObserverMode - netvars::m_hViewModel - sizeof( int ) ];
            int m_iObserverMode;
            char pad_0x33E0[ netvars::m_hObserverTarget - netvars::m_iObserverMode - sizeof( int ) ];
            int m_hObserverTarget;
            char pad_0x35B4[ netvars::m_nTickBase - netvars::m_hObserverTarget - sizeof( int ) ];
            uint32_t m_nTickBase;
            char pad_0x391C[ netvars::m_bIsScoped - netvars::m_nTickBase - sizeof( uint32_t ) ];
            bool m_bIsScoped;
            char pad_0x3930[ netvars::m_bIsDefusing - netvars::m_bIsScoped - sizeof( bool ) ];
            bool m_bIsDefusing;
            char pad_0xA380[ netvars::m_bGunGameImmunity - netvars::m_bIsDefusing - sizeof( bool ) ];
            bool m_bGunGameImmunity;
            char pad_0xA40C[ netvars::m_iShotsFired - netvars::m_bGunGameImmunity - sizeof( bool ) ];
            int m_iShotsFired;
            char pad_0xA40D[ netvars::m_totalHitsOnServer - netvars::m_iShotsFired - sizeof( int ) ];
            int m_totalHitsOnServer;
            char pad_0xA40E[ netvars::m_flHealthShotBoostExpirationTime - netvars::m_totalHitsOnServer - sizeof( int ) ];
            float m_flHealthShotBoostExpirationTime;
            char pad_0xA410[ netvars::m_flFlashMaxAlpha - netvars::m_flHealthShotBoostExpirationTime - sizeof( float ) ];
            float m_flFlashMaxAlpha;
            float m_flFlashDuration;
            char pad_0xB3D4[ netvars::m_iGlowIndex - netvars::m_flFlashDuration - sizeof( float ) ];
            int m_iGlowIndex;
            char pad_0xB3D5[ netvars::m_iCrosshairId - netvars::m_iGlowIndex - sizeof( int ) ];
            int m_iCrosshairId;
        };

        auto crosshair_id( ) {
            return mem->read< int >( address + netvars::m_iCrosshairId );
        }

        auto health( ) {
            return mem->read< int >( address + netvars::m_iHealth );
        }

        auto is_alive( ) {
            return mem->read< int >( address + netvars::m_lifeState ) == 6;
        }

        auto team( ) {
            return mem->read< int >( address + netvars::m_iTeamNum );
        }

        auto flags( ) {
            return mem->read< int >( address + netvars::m_fFlags );
        }

        auto velocity( ) {
            return mem->read< vec3_t >( address + netvars::m_vecVelocity );
        }

        auto dormant( ) {
            return mem->read< bool >( address + signatures::m_bDormant );
        }

        auto class_id( ) {
            const int i_client_networkable = mem->read< int >( address + 0x8 );
            const int get_client_class = mem->read< int >( i_client_networkable + 0x8 );
            const int p_client_class = mem->read< int >( get_client_class + 0x1 );
            return mem->read< int >( p_client_class + 0x14 );
        }

        auto viewmodel( ) {
            auto viewmodel_handle = mem->read< uintptr_t >( address + netvars::m_hViewModel );
            return mem->read< uintptr_t >( mem->client_base + signatures::dwEntityList + ( ( viewmodel_handle & 0xFFF ) - 1 ) * 16 );
        }

        auto glow_index( ) {
            return mem->read< int >( address + netvars::m_iGlowIndex );
        }
    };
}
