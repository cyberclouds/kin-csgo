#pragma once

#include <cstdint>

namespace game {
    struct glow_object_definition_t {
        /*entity_t*/
        void* entity;

        struct {
            float red;
            float green;
            float blue;
        } glow_color;

        float alpha;

    private:
        char pad_0001[ 4 ];
        float pad_0002;

    public:
        float bloom_amount;

    private:
        float pad_0003;

    public:
        bool render_when_occluded;
        bool render_when_unoccluded;
        bool full_bloom_render;

    private:
        char pad_0004[ 1 ];

    public:
        int full_bloom_stencil_test_value;
        int32_t glow_style;
        int32_t split_screen_slot;
        int32_t next_free_slot;

        bool is_unused( ) const {
            return next_free_slot != ENTRY_IN_USE;
        }

        static const int END_OF_FREE_LIST = -1;
        static const int ENTRY_IN_USE = -2;
    };
}
