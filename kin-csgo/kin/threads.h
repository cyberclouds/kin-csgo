#pragma once
#include "../hacks.h"

namespace kin::t {
    inline void kin( ) {
        while ( !GetAsyncKeyState( VK_DELETE ) ) {
            update_menu( );
            std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
        }
    }

    inline void glow( ) {
        while ( !GetAsyncKeyState( VK_DELETE ) ) {
            if ( !ctx->is_connected( ) ) {
                std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
                continue;
            }

            h::triggerbot( );
            h::glow( );

            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }

    inline void entities( ) {
        while ( !GetAsyncKeyState( VK_DELETE ) ) {
            ctx->get_global_vars( ctx->globals );
            ctx->in_game_check( );

            ents->get_local_player_data( ctx->local );
            ents->get_player_data( ctx->player_data );
            bt->update( );
            //aim->update( );

            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }

    inline void bhop( ) {
        while ( !GetAsyncKeyState( VK_DELETE ) ) {
            if ( !ctx->is_connected( ) ) {
                std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
                continue;
            }

            h::bunnyhop( );

            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }

    inline void misc( ) {
        while ( !GetAsyncKeyState( VK_DELETE ) ) {
            if ( !ctx->is_connected( ) ) {
                std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
                continue;
            }

            h::radar( );
            h::hitmarker( );
            h::chams( 0.f, 128.f, 255.f, 45.f );
            h::night_mode( );

            std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
        }
    }

    inline void backtrack( ) {
        while ( !GetAsyncKeyState( VK_DELETE ) ) {
            if ( !ctx->is_connected( ) ) {
                std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
                continue;
            }

            if ( GetAsyncKeyState( VK_LBUTTON ) )
                bt->work( );

            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }

    inline void aimbot( ) {
        while ( !GetAsyncKeyState( VK_DELETE ) ) {
            if ( !ctx->is_connected( ) ) {
                std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
                continue;
            }

            if ( GetAsyncKeyState( VK_LBUTTON ) )
                aim->work( );

            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }
}
