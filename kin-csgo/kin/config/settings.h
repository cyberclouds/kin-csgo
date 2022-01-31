#pragma once

#define SETTING( var, type, value ) type var = value

namespace kin {
    class settings {
    public:
        SETTING( bhop_enabled, bool, false );
        SETTING( chams_enabled, bool, false );
        SETTING( radar_enabled, bool, false );
        SETTING( night_mode_enabled, bool, false );
        SETTING( triggerbot_enabled, bool, false );
        SETTING( glow_enabled, bool, false );
        SETTING( hitmarker_enabled, bool, false );
        SETTING( backtrack_enabled, bool, false );
        SETTING( aimbot_enabled, bool, false );
    };
}

extern std::unique_ptr< kin::settings > cfg;
