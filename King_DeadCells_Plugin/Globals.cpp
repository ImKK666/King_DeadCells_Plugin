#include "stdafx.h"

#include "Globals.hpp"

namespace King {
namespace Native {

Hook< convention_type::cdecl_t, int, wchar_t *, wchar_t *, int > Hook_hl_bytes_compare16;

WNDPROC m_wndProc;
static bool ButtonDown;

class Wrapper {
public:
    static LRESULT __stdcall WndProcCallee( HWND hwnd, UINT m, WPARAM w, LPARAM l ) {
        bool execute = true;
        EventHandler< OnWndProc, evtWndProc, HWND, UINT, WPARAM, LPARAM, bool * >::GetInstance( )->Trigger( hwnd, m, w, l, &execute );

        if( execute ) {
            return CallWindowProc( m_wndProc, hwnd, m, w, l );
        }
        return 1;
    }

    static int _cdecl hl_bytes_compare16_Callee( wchar_t *str1, wchar_t *str2, int len ) {
        // Debug
        {
            //if( ::GetAsyncKeyState( 'R' ) & 0x8000 ) {
            //    if( !ButtonDown ) {
            //        Commander::GetInstance( )->get_logger( )->log( spdlog::level::critical, "-----\n" );
            //    }
            //} else {
            //    ButtonDown = false;
            //}

            //std::wstring log = L"a1:" + std::wstring( a1 ) + L"\na2:" + std::wstring( a2 ) + L"\na3:" + std::to_wstring( a3 );
            //Commander::GetInstance( )->get_logger( )->log( spdlog::level::critical, Crypto::wstring_To_UTF8( log ) );

            //// printf( "a1:%S\na2:%S\na3:%i\n", a1, a2, a3 );

            //int ret = Hook_hl_bytes_compare16.CallOriginal( a1, a2, a3 );
            //log     = L"\nret:" + std::to_wstring( ret );
            //Commander::GetInstance( )->get_logger( )->log( spdlog::level::critical, Crypto::WstringToString( log ).c_str( ) );

            //return ret;
        }

        std::string a { Crypto::wstring_To_UTF8( std::wstring( str1 ) ) };
        std::string b { Crypto::wstring_To_UTF8( std::wstring( str2 ) ) };
        //if( b == a ) {
            // printf( "[%i/%i]:%s\n",b.length(),len, b.c_str( ) );
            //if( b.length( ) == len ) {
                // Commander::GetInstance( )->get_logger( )->log( spdlog::level::critical, b );
                if( b == u8"你不该出发了吗？" ) {
                    printf( "%i/%i\n", b.length( ), len );
                    printf( "触发激活:%s %s\n", Crypto::UTF8ToGBK( a.c_str( ) ), Crypto::UTF8ToGBK( b.c_str( ) ) );
                }
                if( b == u8"看起来我在这里有过不好的回忆。" ) {
                    printf( "%i/%i\n", b.length( ), len );
                    printf( "触发激活:%s %s\n", Crypto::UTF8ToGBK( a.c_str( ) ), Crypto::UTF8ToGBK( b.c_str( ) ) );
                }
            //}
        //}

        return Hook_hl_bytes_compare16.CallOriginal( str1, str2, len );
    }
};

bool Globals::ApplyHooks( ) {
    m_wndProc = reinterpret_cast< WNDPROC >( SetWindowLongPtrA( FindWindowA( nullptr, "HL_WIN" ), GWL_WNDPROC, reinterpret_cast< LONG >( Wrapper::WndProcCallee ) ) );

    Hook_hl_bytes_compare16.Apply( GET_ABSOLUTE_H( Addresses::Globals::hl_bytes_compare16 ), Wrapper::hl_bytes_compare16_Callee );

    return Hook_hl_bytes_compare16.IsApplied( ) && m_wndProc;
}

}   // namespace Native
}   // namespace King
