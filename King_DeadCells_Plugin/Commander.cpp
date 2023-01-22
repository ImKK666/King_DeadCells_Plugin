#include "stdafx.h"

#include "Commander.hpp"

#include "Globals.hpp"

#ifdef _DEBUG
 #define VERIFY_HOOK( CLASS ) if( !##CLASS##::ApplyHooks( ) ) { SPDLOG_ERROR( "HookS Failed! {}", #CLASS ); return false; }
#else
 #define VERIFY_HOOK( CLASS ) if( !##CLASS##::ApplyHooks( ) ) { return false; }
#endif

namespace King {
namespace Native {

std::shared_ptr< Commander > Commander::Instance;
unsigned                     Commander::mImageBase;

Commander::Commander( ) : mLogger( nullptr ), mHookManager( nullptr ) {
    //spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S.%e] [%t] %v" );
    mLogger = spdlog::basic_logger_mt( "file_logger", "logs/King-log.txt" );
    mLogger->flush_on( spdlog::level::trace );

    mHookManager = std::make_shared< HookManager >( );
}

std::shared_ptr< Commander > Commander::GetInstance( ) {
    if( !Instance ) {
        Instance = std::make_shared< Commander >( );
    }
    return Instance;
}

std::shared_ptr< spdlog::logger > Commander::get_logger( ) const {
    return mLogger;
}
std::shared_ptr< HookManager > Commander::get_hookManager( ) const {
    return mHookManager;
}

bool Commander::ApplyHooks( ) const {
    if( !mHookManager ) {
        return false;
    }

    //VERIFY_HOOK( Globals )

    return true;
}

bool Commander::RemoveHooks( ) const {
    if( !mHookManager ) {
        return false;
    }

    return mHookManager->UnloadHooks( );
}

bool Commander::LinkHooks( ) const {
    if( !mHookManager ) {
        return false;
    }

    // Globals !
    LINK_EVENT( OnWndProc, evtWndProc, HWND, UINT, WPARAM, LPARAM, bool * )



    return true;
}

}   // namespace Native
}   // namespace King