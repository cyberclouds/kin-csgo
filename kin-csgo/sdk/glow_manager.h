#pragma once

#include "glow_object_definition.h"
#include "cutlvector.h"

namespace game {
    class glow_object_manager {
    public:
        c_utl_vector< glow_object_definition_t > m_glow_objects;
        int m_first_free_slot;
    };
}
