#pragma once

namespace King {
namespace Native {
namespace Dump {

const unsigned GeneralError   = 0xA0000000;

enum class ErrorCode : unsigned {
    UnhandledException     = GeneralError | 0x0,
    CppException           = GeneralError | 0x1,
};

void ReportFatalError( EXCEPTION_POINTERS *ex, ErrorCode code, const std::string &customMessage );
void ReportFatalError( EXCEPTION_POINTERS *ex, ErrorCode code );

}   // namespace Dump
}   // namespace Native
}   // namespace King