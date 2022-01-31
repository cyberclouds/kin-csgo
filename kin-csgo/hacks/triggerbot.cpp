#include "triggerbot.h"
#include "../sdk.h"
#include "../kin.h"

void kin::h::triggerbot( ) {
    if ( !cfg->triggerbot_enabled || !GetAsyncKeyState( VK_XBUTTON1 ) || !ctx->is_connected( ) )
        return;

    if ( ctx->local.m_iCrosshairId < 1 || ctx->local.m_iCrosshairId > 64 )
        return;

    game::entity_t::player_data_t e;

    for ( auto p : ctx->player_data ) {
        if ( p.index == ctx->local.m_iCrosshairId ) {
            e = p;
            break;
        }
    }

    if ( e.m_iTeamNum == ctx->local.m_iTeamNum )
        return;

    mem->write< int >( mem->client_base + game::signatures::dwForceAttack, 6 );
}
