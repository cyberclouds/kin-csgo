#pragma once

#include "entity.h"
#include "../kin/mem.h"
#include "../kin/globals.h"
#include "offsets.h"
#include "classid.h"
#include <vector>

namespace game {
    class entity_list {
    public:
        entity_t get_entity_by_index( const int i ) {
            return entity_t( mem->read< uint32_t >( mem->client_base + signatures::dwEntityList + ( i - 1 ) * 0x10 ), i );
        }

        entity_t::player_data_t get_player_data_by_index( const int i ) {
            auto add = mem->read< uint32_t >( mem->client_base + signatures::dwEntityList + ( i - 1 ) * 0x10 );
            /*auto class_id = mem->read< int >( mem->read< int >( mem->read< int >( mem->read< int >( add + 0x8 ) + 0x8 ) + 0x1 ) + 0x14 );
            if ( class_id != CCSPlayer )
                return entity_t::player_data_t{ 0 };*/ // comment it out for now, wasting way too much cpu cycles
            auto player = mem->read< entity_t::player_data_t >( add );
            player.address = add;
            return player;
        }

        static void get_local_player_data( entity_t::player_data_t& p ) {
            if ( !ctx->is_connected( ) )
                return;
            auto add = mem->read< uint32_t >( mem->client_base + signatures::dwLocalPlayer );
            p = mem->read< entity_t::player_data_t >( add );
            p.address = add;
        }

        void get_player_data( std::vector< entity_t::player_data_t >& v ) {
            v.clear( );
            if ( !ctx->is_connected( ) )
                return;

            for ( auto i = 1; i <= ctx->globals.max_clients; ++i ) {
                auto e = get_player_data_by_index( i );
                /*if ( !e.address )
                   continue;*/
                v.push_back( e );
            }
        }
    };
}

extern std::unique_ptr< game::entity_list > ents;
