#include "kin.h"

std::unique_ptr< kin::memory > mem;
std::unique_ptr< kin::settings > cfg;
std::unique_ptr< game::entity_list > ents;
std::unique_ptr< kin::context > ctx;
std::unique_ptr< kin::h::backtrack > bt;
std::unique_ptr< kin::h::aimbot > aim;

int main( ) {
    kin::init( );
    kin::draw_logo( );
    kin::spacer( );

    mem = std::make_unique< kin::memory >( );
    cfg = std::make_unique< kin::settings >( );
    ents = std::make_unique< game::entity_list >( );
    ctx = std::make_unique< kin::context >( );
    bt = std::make_unique< kin::h::backtrack >( );
    aim = std::make_unique< kin::h::aimbot >( );

#ifndef NDEBUG
    kin::spacer( );
#endif
    {
        kin::log( "features:" );
        kin::feature( "NUMPAD1", "bunnyhop", cfg->bhop_enabled );
        kin::feature( "NUMPAD2", "radar", cfg->radar_enabled );
        kin::feature( "NUMPAD3", "chams", cfg->chams_enabled );
        kin::feature( "NUMPAD4", "night mode", cfg->night_mode_enabled );
        kin::feature( "NUMPAD5", "triggerbot - MOUSE4", cfg->triggerbot_enabled );
        kin::feature( "NUMPAD6", "glow", cfg->glow_enabled );
        kin::feature( "NUMPAD0", "hitmarker", cfg->hitmarker_enabled );
        kin::feature( "NUMPAD.", "backtrack", cfg->backtrack_enabled );
        //kin::feature( "NUMPAD+", "aimbot >:(", cfg->aimbot_enabled );
        kin::log( "press [DEL] to quit" );
    }
    kin::spacer( );

    std::thread t1( kin::t::kin );
    t1.detach( );

    std::thread t2( kin::t::entities );
    t2.detach( );

    std::thread t3( kin::t::bhop );
    t3.detach( );

    std::thread t4( kin::t::glow );
    t4.detach( );

    std::thread t5( kin::t::misc );
    t5.detach( );

    std::thread t6( kin::t::backtrack );
    t6.detach( );

    //std::thread t7( kin::t::aimbot );
    //t7.detach( );

    while ( !GetAsyncKeyState( VK_DELETE ) ) {
        std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );
    }

    ctx->send_packet( true );

    kin::h::chams_cleanup( );
    kin::h::night_mode_cleanup( );

    kin::log( "goodbye..." );
    Beep( 600, 150 );

    return 0;
}
