#include "stdafx.h"

#include <detours/detours.h>
#include <detours/detver.h>

namespace King {
namespace Native {
void *HookManager::Install( void *target, void *detour ) {
    DetourTransactionBegin( );
    DetourUpdateThread( GetCurrentThread( ) );

    PDETOUR_TRAMPOLINE trampoline;
    DetourAttachEx( &target, detour, &trampoline, nullptr, nullptr );
    if( const auto error = DetourTransactionCommit( ) != NO_ERROR ) {
        SPDLOG_ERROR( "hook install {} failed - error {} ", target, error );
    }
    if( trampoline ) {
        m_hookList.push_back( HookEntry( trampoline, target, detour ) );
    }

    return trampoline;
}

bool HookManager::UnloadHooks( ) const {
    for( auto hookEntry : m_hookList ) {
        DetourTransactionBegin( );
        DetourUpdateThread( GetCurrentThread( ) );
        DetourDetach( &hookEntry.m_original, hookEntry.m_detour );
        if( const auto error = DetourTransactionCommit( ) != NO_ERROR ) {
            SPDLOG_ERROR( "hook unload {} failed - error {} ", hookEntry.m_original, error );
        }
    }
    return true;
}

}   // namespace Native
}   // namespace King
