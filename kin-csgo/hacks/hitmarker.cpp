#include "hitmarker.h"
#include "../sdk.h"

void kin::h::hitmarker( ) {
    if ( !cfg->hitmarker_enabled || !ctx->is_connected( ) )
        return;

    static auto hits = 0;
    int current_hits = ctx->local.m_totalHitsOnServer;
    if ( hits != current_hits && current_hits != 0 ) {
        hits = current_hits;
        mem->write< float >( ctx->local.address + game::netvars::m_flHealthShotBoostExpirationTime, ctx->globals.curtime + .5f );
    }
}
