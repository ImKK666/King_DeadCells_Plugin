#include "stdafx.h"

#include "Dump.hpp"

DWORD WINAPI InitThread( ) {
    AllocConsole( );
    FILE *file;
    freopen_s( &file, "CONIN$", "r", stdin );
    freopen_s( &file, "CONOUT$", "w", stdout );

    spdlog::set_level( spdlog::level::trace );

    try {
        SPDLOG_INFO( "Applying hook services" );
        if( !King::Native::Commander::GetInstance( )->ApplyHooks( ) ) {
            SPDLOG_ERROR( "Hooking Service Failed!" );
        }

        SPDLOG_INFO( "Applying link hooks" );
        if( !King::Native::Commander::GetInstance( )->LinkHooks( ) ) {
            SPDLOG_ERROR( "Link Hooks Failed!" );
        }

    } catch( std::exception &ex ) {
        ReportFatalError( nullptr, King::Native::Dump::ErrorCode::CppException, ex.what( ) );
    } catch( ... ) {
        ReportFatalError( nullptr, King::Native::Dump::ErrorCode::CppException );
    }

    return 0;
}

LONG WINAPI Handler( EXCEPTION_POINTERS *info ) {
    if( info->ExceptionRecord->ExceptionCode == 0x406D1388 ) {
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved ) {
    switch( ul_reason_for_call ) {
    case DLL_PROCESS_ATTACH :
        {
            AddVectoredExceptionHandler( 0, Handler );

            // Initial setup
            King::Native::Commander::mImageBase = reinterpret_cast< unsigned >( hModule );
            mModuleBase                         = reinterpret_cast< unsigned >( GetModuleHandle( NULL ) );
            mLibhlBase                          = reinterpret_cast< unsigned >( GetModuleHandle( L"libhl.dll" ) );

            std::thread( InitThread ).detach( );
        }
    case DLL_PROCESS_DETACH :
        {
            King::Native::Commander::GetInstance( )->RemoveHooks( );
        }
    default :
        {
            break;
        }
    }
    return TRUE;
}