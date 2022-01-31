#pragma once
#include <iostream>
#include <string_view>
#include <windows.h>
#include "config/settings.h"
#include <thread>
#include <string>

namespace kin {
    inline void init( ) {
        const std::string title = "// KIN // alpha, built on ";
        const std::string date = __DATE__;
        const std::string time = __TIME__;
        SetConsoleTitleA( ( title + date + " " + time ).c_str( ) );
    }

    inline void draw_logo( ) {
        auto logo = R"(
__/\\\________/\\\__/\\\\\\\\\\\__/\\\\\_____/\\\_        
 _\/\\\_____/\\\//__\/////\\\///__\/\\\\\\___\/\\\_       
  _\/\\\__/\\\//_________\/\\\_____\/\\\/\\\__\/\\\_      
   _\/\\\\\\//\\\_________\/\\\_____\/\\\//\\\_\/\\\_     
    _\/\\\//_\//\\\________\/\\\_____\/\\\\//\\\\/\\\_    
     _\/\\\____\//\\\_______\/\\\_____\/\\\_\//\\\/\\\_   
      _\/\\\_____\//\\\______\/\\\_____\/\\\__\//\\\\\\_  
       _\/\\\______\//\\\__/\\\\\\\\\\\_\/\\\___\//\\\\\_ 
        _\///________\///__\///////////__\///_____\/////__)";
        std::cout << logo << std::endl;
    }

    inline void log( std::string_view message ) {
        std::cout << "        __ " << message << std::endl;
    }

    inline void feature( std::string_view hotkey, std::string_view name, bool state ) {
        std::cout << "        __ [" << hotkey << "] " << name << " " << ( state ? "[ON]" : "[OFF]" ) << std::endl;
    }

    inline void spacer( ) {
        std::cout << "        ________________________________________________________" << std::endl
                << "        __ " << std::endl;
    }

    inline void refresh( ) {
        system( "cls" );
        draw_logo( );
        spacer( );
        {
            log( "features:" );
            feature( "NUMPAD1", "bunnyhop", cfg->bhop_enabled );
            feature( "NUMPAD2", "radar", cfg->radar_enabled );
            feature( "NUMPAD3", "chams", cfg->chams_enabled );
            feature( "NUMPAD4", "night mode", cfg->night_mode_enabled );
            feature( "NUMPAD5", "triggerbot - MOUSE4", cfg->triggerbot_enabled );
            feature( "NUMPAD6", "glow", cfg->glow_enabled );
            feature( "NUMPAD0", "hitmarker", cfg->hitmarker_enabled );
            feature( "NUMPAD.", "backtrack", cfg->backtrack_enabled );
            feature( "NUMPAD+", "aimbot", cfg->aimbot_enabled );
            log( "press [DEL] to quit" );
        }
        spacer( );
    }

    inline void update_menu( ) {
        bool update = false;
        if ( GetAsyncKeyState( VK_NUMPAD1 ) ) {
            cfg->bhop_enabled = !cfg->bhop_enabled;
            update = true;
        }
        if ( GetAsyncKeyState( VK_NUMPAD2 ) ) {
            cfg->radar_enabled = !cfg->radar_enabled;
            update = true;
        }
        if ( GetAsyncKeyState( VK_NUMPAD3 ) ) {
            cfg->chams_enabled = !cfg->chams_enabled;
            update = true;
        }
        if ( GetAsyncKeyState( VK_NUMPAD4 ) ) {
            cfg->night_mode_enabled = !cfg->night_mode_enabled;
            update = true;
        }
        if ( GetAsyncKeyState( VK_NUMPAD5 ) ) {
            cfg->triggerbot_enabled = !cfg->triggerbot_enabled;
            update = true;
        }
        if ( GetAsyncKeyState( VK_NUMPAD6 ) ) {
            cfg->glow_enabled = !cfg->glow_enabled;
            update = true;
        }
        if ( GetAsyncKeyState( VK_NUMPAD0 ) ) {
            cfg->hitmarker_enabled = !cfg->hitmarker_enabled;
            update = true;
        }
        if ( GetAsyncKeyState( VK_DECIMAL ) ) {
            cfg->backtrack_enabled = !cfg->backtrack_enabled;
            update = true;
        }
        if ( GetAsyncKeyState( VK_ADD ) ) {
            cfg->aimbot_enabled = !cfg->aimbot_enabled;
            update = true;
        }
        if ( update ) {
            refresh( );
            Beep( 400, 100 );
        }
    }
}
