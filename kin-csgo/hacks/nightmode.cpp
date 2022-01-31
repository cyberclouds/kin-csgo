#include "nightmode.h"
#include "../sdk.h"
#include "../kin.h"

void kin::h::night_mode( ) {
    static bool once = false;
    static bool cleanup = true;
    if ( !cfg->night_mode_enabled ) {
        if ( cleanup )
            night_mode_cleanup( );
        cleanup = false;
        once = false;
        return;
    }
    cleanup = true;

    if ( !ctx->is_connected( ) ) {
        // TODO: engine class
        once = false;
        return;
    }

    if ( once )
        return;

    for ( auto i = 0; i < 2048; ++i ) {
        auto e = ents->get_entity_by_index( i );

        if ( e.class_id( ) != game::ClassID_t::CEnvTonemapController )
            continue;

        mem->write< byte >( e.address + game::netvars::m_bUseCustomAutoExposureMin, 1 );
        mem->write< byte >( e.address + game::netvars::m_bUseCustomAutoExposureMax, 1 );
        mem->write< float >( e.address + game::netvars::m_flCustomAutoExposureMin, 0.075f );
        mem->write< float >( e.address + game::netvars::m_flCustomAutoExposureMax, 0.075f );
        once = true;
        break;
    }
}

void kin::h::night_mode_cleanup( ) {
    for ( auto i = 0; i < 2048; ++i ) {
        auto e = ents->get_entity_by_index( i );

        if ( e.class_id( ) != game::ClassID_t::CEnvTonemapController )
            continue;

        mem->write< byte >( e.address + game::netvars::m_bUseCustomAutoExposureMin, 0 );
        mem->write< byte >( e.address + game::netvars::m_bUseCustomAutoExposureMax, 0 );
        mem->write< float >( e.address + game::netvars::m_flCustomAutoExposureMin, 0.8f );
        mem->write< float >( e.address + game::netvars::m_flCustomAutoExposureMax, 1.3f );
        break;
    }
}
