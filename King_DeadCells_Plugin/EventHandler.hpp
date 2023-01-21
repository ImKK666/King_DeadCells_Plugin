#pragma once

#include "Common.hpp"

#include <vector>
#include <d3dx9.h>
#include <windows.h>

#include "EventType.hpp"

#ifdef N_MANAGED_BUILD
 #undef KING_API
 #define KING_API __declspec( dllimport )
#endif

#define LINK_EVENT( NUM, SKELETON, ... )                                                                                                                                           \
 EventHandler< ##NUM##, ##SKELETON##, __VA_ARGS__## >::GetInstance( )->Add( nullptr );                                                                                             \
 EventHandler< ##NUM##, ##SKELETON##, __VA_ARGS__## >::GetInstance( )->Remove( nullptr );
#define LINK_EVENT_T( NUM, SKELETON, ... ) template class KING_API EventHandler< ##NUM##, ##SKELETON##, __VA_ARGS__## >;

namespace King {
namespace Native {

// Globals !
typedef void( evtWndProc )( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, bool *execute );

// ##=======================================================================##//
template< int uniqueEventNumber, typename skeleton, typename... TArgs >
class KING_API EventHandler {

private:
    std::vector< void * > m_eventCallbacks;

public:
    EventHandler( ) {
    }

    static __declspec( noinline ) EventHandler *GetInstance( ) {
        static EventHandler *instance;
        if( instance == nullptr ) {
            instance = new EventHandler( );
        }

        return instance;
    }

    void __declspec( noinline ) Add( void *callback ) {
        if( callback != nullptr ) {
            m_eventCallbacks.push_back( callback );
        }
    }

    void __declspec( noinline ) Remove( void *listener ) {
        if( listener == nullptr ) {
            return;
        }

        auto eventPtr = find( m_eventCallbacks.begin( ), m_eventCallbacks.end( ), listener );
        if( eventPtr != m_eventCallbacks.end( ) ) {
            m_eventCallbacks.erase( find( m_eventCallbacks.begin( ), m_eventCallbacks.end( ), listener ) );
        }
    }

    bool __cdecl Trigger( TArgs... args ) {
        for( auto i = m_eventCallbacks.size( ); i-- > 0; ) {
            auto ptr = m_eventCallbacks [ i ];
            if( ptr != nullptr ) {
                static_cast< skeleton * >( ptr )( args... );
            }
        }

        return true;
    }
};

// Globals !
LINK_EVENT_T( OnWndProc, evtWndProc, HWND, UINT, WPARAM, LPARAM, bool * )




}   // namespace Native
}   // namespace King
