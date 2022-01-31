#include "radar.h"
#include "../kin.h"

void kin::h::radar( ) {
    if ( !cfg->radar_enabled || !ctx->is_connected( ) )
        return;

    for ( auto e : ctx->player_data ) {
        if ( e.m_bDormant || e.m_iTeamNum == ctx->local.m_iTeamNum )
            continue;

        mem->write< bool >( e.address + game::netvars::m_bSpotted, true );
    }
}
