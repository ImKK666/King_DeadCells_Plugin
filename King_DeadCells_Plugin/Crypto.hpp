#pragma once

#include <string>
#include <vector>

namespace King {
namespace Native {
namespace Crypto {

std::vector< unsigned char > StringToByteVector( const std::string &str );
std::string                  ByteVectorToString( const std::vector< unsigned char > &vec );
std::vector< unsigned char > HexStringToByteVector( const std::string &hex );
std::string                  ByteVectorToHexString( const std::vector< unsigned char > &vec );

std::string Base64Encode( const std::string &data );
std::string Base64Decode( const std::string &data );

std::string Base64Encode( const std::vector< unsigned char > &data );
std::string Base64Decode( const std::vector< unsigned char > &data );

std::string CreateGuid( );

unsigned FNV_1a( const unsigned char *data, unsigned length );

constexpr unsigned val_32_const = 0x4508063;
inline constexpr unsigned FNV_1a( const char *const str, const unsigned value = val_32_const ) noexcept {
    return ( str [ 0 ] == '\0' ) ? value : FNV_1a( &str [ 1 ], ( value ^ str [ 0 ] ) * 0x1000193 );
}

const char *UTF8ToGBK( const char *strUTF8 );
char       *wstring_To_UTF8( const std::wstring &str );

std::string WstringToString( const std::wstring wstr );

}   // namespace Crypto
}   // namespace Native
}   // namespace King
