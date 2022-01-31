#include "mem.h"

bool kin::memory::attach_process( const char* process_name ) {
    HANDLE h_pid = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
    PROCESSENTRY32 proc_entry;
    proc_entry.dwSize = sizeof( proc_entry );

    do {
        if ( !strcmp( proc_entry.szExeFile, process_name ) ) {
#ifndef NDEBUG
            log( "found cs:go" );
#endif
            this->pid = proc_entry.th32ProcessID;
            CloseHandle( h_pid );
            this->process = OpenProcess( PROCESS_ALL_ACCESS, FALSE, this->pid );
            return true;
        }
    }
    while ( Process32Next( h_pid, &proc_entry ) );

    CloseHandle( h_pid );
    return false;
}

MODULEENTRY32 kin::memory::get_module( const char* module_name ) {
    HANDLE h_module = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pid );
    MODULEENTRY32 entry;
    entry.dwSize = sizeof( entry );

    do {
        if ( !strcmp( entry.szModule, module_name ) ) {
#ifndef NDEBUG
            kin::log( std::string( "found " ) + module_name );
#endif
            CloseHandle( h_module );
            return entry;
        }
    }
    while ( Module32Next( h_module, &entry ) );

    CloseHandle( h_module );
    entry.modBaseAddr = nullptr;
    return entry;
}
