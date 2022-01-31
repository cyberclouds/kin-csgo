#include "glow.h"
#include "../sdk.h"

void kin::h::glow( ) {
    if ( !cfg->glow_enabled || !ctx->is_connected( ) )
        return;

    auto glow_manager = mem->read< uint32_t >( mem->client_base + game::signatures::dwGlowObjectManager );

    for ( auto& e : ctx->player_data ) {
        if ( e.m_iTeamNum == ctx->local.m_iTeamNum )
            continue;

        auto glow_object = mem->read< game::glow_object_definition_t >( glow_manager + e.m_iGlowIndex * 0x38 );

        auto hp = e.m_iHealth;

        glow_object.glow_color = { ( 255.f - ( hp * 2.55f ) ) / 255.f, hp * 2.55f / 255.f, 0.f };
        glow_object.alpha = 0.8f;
        glow_object.render_when_occluded = true;
        glow_object.render_when_unoccluded = false;
        glow_object.bloom_amount = 1.f;
        //glow_object.glow_style = 0;
        glow_object.full_bloom_render = e.m_bIsDefusing ? true : false;
        //glow_object.full_bloom_stencil_test_value = 0;

        mem->write< game::glow_object_definition_t >( glow_manager + e.m_iGlowIndex * 0x38, glow_object );
    }
}
