#pragma once

#include <vector>

#include "Commander.hpp"

#define MANUAL_ENTRY       _asm pushad _asm pushfd
#define MANUAL_EXIT( RET ) _asm popfd _asm popad _asm jmp RET

namespace King {
namespace Native {

enum class convention_type {
    stdcall_t,
    cdecl_t,
    thiscall_t,
    fastcall_t,
};

template< convention_type tp, typename retn, typename... args >
struct convention;

template< typename retn, typename... args >
struct convention< convention_type::stdcall_t, retn, args... > {
    typedef retn( __stdcall *type )( args... );
};

template< typename retn, typename... args >
struct convention< convention_type::cdecl_t, retn, args... > {
    typedef retn( __cdecl *type )( args... );
};

template< typename retn, typename... args >
struct convention< convention_type::thiscall_t, retn, args... > {
    typedef retn( __thiscall *type )( args... );
};

template< typename retn, typename... args >
struct convention< convention_type::fastcall_t, retn, args... > {
    typedef retn( __fastcall *type )( args... );
};

struct HookEntry {
    void *m_original;
    void *m_target;
    void *m_detour;

    HookEntry( void *original, void *target, void *detour ) : m_original( original ), m_target( target ), m_detour( detour ) {
    }
};

class HookManager {

private:
    std::vector< HookEntry > m_hookList;

public:
    void *Install( void *target, void *detour );
    bool  UnloadHooks( ) const;
};

template< convention_type tp = convention_type::cdecl_t, typename retn = void, typename... args >
class Hook {

private:
    bool m_isApplied;

public:
    typedef typename convention< tp, retn, args... >::type type;

    type m_original;
    type m_detour;

    Hook( ) : m_isApplied( false ), m_original( nullptr ), m_detour( nullptr ) {
    }

    template< typename T >
    Hook( T func, type detour ) {
        Apply< T >( func, detour );
    }

    template< typename T >
    void Apply( T func, type detour ) {
        if( m_isApplied ) {
            return;
        }

        m_detour   = detour;
        m_original = reinterpret_cast< type >( Commander::GetInstance( )->get_hookManager( )->Install( reinterpret_cast< void * >( func ), reinterpret_cast< void * >( detour ) ) );
        if( m_original ) {
            m_isApplied = true;
        }
    }

    retn CallOriginal( args... p ) {
        return m_original( p... );
    }

    retn CallDetour( args... p ) {
        return m_detour( p... );
    }

    bool IsApplied( ) const {
        return m_isApplied;
    }
};

}   // namespace Native
}   // namespace King
