#include "stdafx.h"

#include "Dump.hpp"

namespace King {
namespace Native {
namespace Dump {

void ReportFatalError( EXCEPTION_POINTERS *ex, ErrorCode code ) {
    ReportFatalError( ex, code, "" );
}

void ReportFatalError( EXCEPTION_POINTERS *ex, ErrorCode code, const std::string &message ) {
    std::stringstream ss;
    ss << "A fatal error occured (code: " << fmt::format( "{}", static_cast< unsigned >( code ) ) << ").\n";
    ss << "Please report this to the developers to aid in fixing the issue.\n";
    ss << "Please COPY AND PASTE the contents of this message box (Ctrl + C when selected) instead of taking a screenshot.\n\n";

    const auto codeType = static_cast< unsigned >( code ) & 0xF0000000;
    if( message != "" || codeType == GeneralError && ex ) {
        ss << "Additional Information:\n";
        if( message != "" ) {
            ss << "------------message: " << message << "\n";
        }
        if( codeType == GeneralError && ex ) {
            std::stringstream sss;

            sss << "game  base: " << fmt::format( "{}", mModuleBase ) << "\n";
            sss << "core  base: " << fmt::format( "{}", reinterpret_cast< unsigned >( GetModuleHandle( L"King_DeadCells_Plugin.dll" ) ) ) << "\n";
            sss << "libhl base: " << fmt::format( "{}", mLibhlBase ) << "\n";
            sss << "address: " << fmt::format( "{}", ex->ExceptionRecord->ExceptionAddress ) << "\n";
            sss << "code: " << fmt::format( "{}", ex->ExceptionRecord->ExceptionCode ) << "\n";
            sss << "stack: " << fmt::format( "{}", ex->ContextRecord->Esp ) << "\n";
            sss << "trace: ";

            // 3 x 12
            const auto stack = reinterpret_cast< unsigned * >( ex->ContextRecord->Esp );
            for( int i = 0; i < 12; i++ ) {
                for( int ii = 0; ii < 3; ii++ ) {
                    sss << fmt::format( "{} ", stack [ i + ii ] ).c_str( );
                }
                sss << "\n";
            }

            const auto string = Crypto::Base64Encode( sss.str( ) );

            ss << "------------------info: " << string << "\n";
        }
    }

    MessageBoxA( nullptr, ss.str( ).c_str( ), "Fatal Error", MB_OK | MB_ICONERROR );
}

}   // namespace Dump
}   // namespace Native
}   // namespace King
