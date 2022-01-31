#include "bunnyhop.h"
#include "../sdk.h"
#include "../kin.h"

#define	FL_ONGROUND ( 1 << 0 )

void kin::h::bunnyhop( ) {
    if ( !cfg->bhop_enabled || !ctx->is_connected( ) )
        return;

    /*const uint32_t ptr = static_cast< int >( mem->client_base + game::signatures::dwMouseEnablePtr );
    auto mou = mem->read< uint32_t >( mem->client_base + game::signatures::dwMouseEnable );
    mou ^= ptr;
    auto m = *reinterpret_cast< int* >( &mou );
    if ( m != 1 )
        return;*/

    if ( ctx->local.m_vecVelocity.length_2d( ) < 0.5f ) // TODO: IMPLEMENT A NETVAR MANAGER
        return;

    if ( GetAsyncKeyState( VK_SPACE ) && ctx->local.m_fFlags & FL_ONGROUND )
        mem->write< int >( mem->client_base + game::signatures::dwForceJump, 6 );
}
