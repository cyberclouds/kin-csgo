#pragma once
#include "log.h"
#include <windows.h>
#include <thread>
#include <TlHelp32.h>
#include <iostream>

namespace kin {
    class memory {
        uintptr_t pid;
        HANDLE process;
    public:
        uintptr_t get_pid( ) {
            return this->pid;
        }

        HANDLE get_process_handle( ) {
            return this->process;
        }

        MODULEENTRY32 client;
        MODULEENTRY32 engine;
        uintptr_t client_base, engine_base,
                  client_size, engine_size;

        bool attach_process( const char* process_name );
        MODULEENTRY32 get_module( const char* module_name );

        template< typename T >
        T read( const uintptr_t address ) {
            T val;
            ReadProcessMemory( process, reinterpret_cast< LPVOID >( address ), &val, sizeof( T ), nullptr );
            return val;
        }

        template< typename T >
        BOOL write( const uintptr_t address, T value ) {
            return WriteProcessMemory( process, reinterpret_cast< LPVOID >( address ), &value, sizeof( T ), nullptr );
        }

        memory( ) {
            this->process = nullptr;
            this->pid = -1;
            try {
                if ( !attach_process( "csgo.exe" ) )
                    throw 1;
                this->client = get_module( "client.dll" );
                this->engine = get_module( "engine.dll" );
                this->client_base = reinterpret_cast< uintptr_t >( this->client.modBaseAddr );
                this->engine_base = reinterpret_cast< uintptr_t >( this->engine.modBaseAddr );
                if ( !this->client_base )
                    throw 2;
                if ( !this->engine_base )
                    throw 3;
                this->client_size = this->client.dwSize;
                this->engine_size = this->engine.dwSize;
            }
            catch ( int exception ) {
                switch ( exception ) {
                    case 1:
                        MessageBoxA( nullptr, "cs:go is not running", "kin", MB_ICONSTOP | MB_OK );
                        exit( NULL );
                    case 2:
                        MessageBoxA( nullptr, "could not find client.dll", "kin", MB_ICONSTOP | MB_OK );
                        exit( NULL );
                    case 3:
                        MessageBoxA( nullptr, "could not find engine.dll", "kin", MB_ICONSTOP | MB_OK );
                        exit( NULL );
                    default:
                        throw;
                }
            }
            catch ( ... ) {
                MessageBoxA( nullptr, "unhandled exception thrown", "kin", MB_ICONSTOP | MB_OK );
                exit( NULL );
            }
        }

        ~memory( ) {
            CloseHandle( this->process );
        }
    };
}

extern std::unique_ptr< kin::memory > mem;
