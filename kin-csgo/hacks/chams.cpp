#include "chams.h"
#include "../kin.h"

struct clr_t {
    clr_t( float r, float g, float b, float a ) {
        red = static_cast< byte >( r );
        green = static_cast< byte >( g );
        blue = static_cast< byte >( b );
        alpha = static_cast< byte >( a );
    }

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

void kin::h::chams( float r, float g, float b, float brightness ) {
    static bool cleanup = true;
    static bool once = false;

    if ( !cfg->chams_enabled ) {
        if ( cleanup ) {
            chams_cleanup( );
            cleanup = false;
        }
        once = false;
        return;
    }
    cleanup = true;

    const clr_t color = { r, g, b, 255.f };
    const clr_t color_team = { 255.f / ( brightness / 5.f ), 255.f / ( brightness / 5.f ), 255.f / ( brightness / 5.f ), 255.f };

    for ( auto e : ctx->player_data ) {
        mem->write< clr_t >( mem->read< uint32_t >( mem->client_base + game::signatures::dwEntityList + ( ( e.m_hViewModel & 0xFFF ) - 1 ) * 16 ) + game::netvars::m_clrRender, color_team );

        if ( e.m_iTeamNum == ctx->local.m_iTeamNum )
            mem->write< clr_t >( e.address + game::netvars::m_clrRender, color_team );
        else
            mem->write< clr_t >( e.address + game::netvars::m_clrRender, color );
    }

    if ( once )
        return;

    const uint32_t this_ptr = static_cast< int >( mem->engine_base + game::signatures::model_ambient_min - 0x2c );
    auto xored = *reinterpret_cast< uint32_t* >( &brightness ) ^ this_ptr;
    mem->write< int >( mem->engine_base + game::signatures::model_ambient_min, xored );
    once = true;
}

void kin::h::chams_cleanup( ) {
    for ( auto e : ctx->player_data ) {
        mem->write< clr_t >( mem->read< uint32_t >( mem->client_base + game::signatures::dwEntityList + ( ( e.m_hViewModel & 0xFFF ) - 1 ) * 16 ) + game::netvars::m_clrRender, clr_t( 255.f, 255.f, 255.f, 255.f ) );
        mem->write< clr_t >( e.address + game::netvars::m_clrRender, clr_t( 255.f, 255.f, 255.f, 255.f ) );
    }
    float brightness = 0.f;
    const uint32_t this_ptr = static_cast< int >( mem->engine_base + game::signatures::model_ambient_min - 0x2c );
    auto xored = *reinterpret_cast< uint32_t* >( &brightness ) ^ this_ptr;
    mem->write< int >( mem->engine_base + game::signatures::model_ambient_min, xored );
}
