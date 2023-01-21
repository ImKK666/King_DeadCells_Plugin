#pragma once

namespace King {
namespace Native {
namespace Dump {

const unsigned GeneralError   = 0xA0000000;
const unsigned AntiCheatError = 0xB0000000;
const unsigned ImplError      = 0xC0000000;

enum class ErrorCode : unsigned {
    UnhandledException     = GeneralError | 0x0,
    CppException           = GeneralError | 0x1,

    UnexpectedChallenge    = AntiCheatError | 0x0,
    UnimplementedEmulation = AntiCheatError | 0x1,
    UninitializedEmulation = AntiCheatError | 0x2,
    ProcessIntegrityCheck  = AntiCheatError | 0x3,

    WebsocketNonExistent   = ImplError | 0x0,
    HanbotDetected         = ImplError | 0x1,
    NoSubscription         = ImplError | 0x2,
    HwidMismatch           = ImplError | 0x3,
};

void ReportFatalError( EXCEPTION_POINTERS *ex, ErrorCode code, const std::string &customMessage );
void ReportFatalError( EXCEPTION_POINTERS *ex, ErrorCode code );

}   // namespace Dump
}   // namespace Native
}   // namespace King