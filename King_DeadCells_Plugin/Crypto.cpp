#include "stdafx.h"

#include "Crypto.hpp"
#include <Base64.hpp>
#include <codecvt>
#include <iomanip>

namespace King {
namespace Native {
namespace Crypto {

std::vector< unsigned char > StringToByteVector( const std::string &str ) {
    return std::vector< unsigned char >( str.begin( ), str.end( ) );
}

std::string ByteVectorToString( const std::vector< unsigned char > &vec ) {
    return std::string( vec.begin( ), vec.end( ) );
}

std::vector< unsigned char > HexStringToByteVector( const std::string &hex ) {
    std::vector< unsigned char > bytes;

    for( unsigned int i = 0; i < hex.length( ); i += 2 ) {
        std::string byteString = hex.substr( i, 2 );
        auto        byte       = static_cast< unsigned char >( strtol( byteString.c_str( ), nullptr, 16 ) );
        bytes.push_back( byte );
    }

    return bytes;
}

std::string ByteVectorToHexString( const std::vector< unsigned char > &vec ) {
    std::stringstream ss;

    for( auto byte : vec ) {
        ss << std::hex << std::setfill( '0' ) << byte;
    }

    return ss.str( );
}

std::string Base64Encode( const std::string &data ) {
    std::string out;

    Base64::Encode( data, &out );

    return out;
}

std::string Base64Decode( const std::string &data ) {
    std::string out;

    Base64::Decode( data, &out );

    return out;
}

std::string Base64Encode( const std::vector< unsigned char > &data ) {
    return Base64Encode( ByteVectorToString( data ) );
}

std::string Base64Decode( const std::vector< unsigned char > &data ) {
    return Base64Decode( ByteVectorToString( data ) );
}

std::string CreateGuid( ) {
    GUID guid;
    CoCreateGuid( &guid );
    char guid_cstr [ 39 ];
    snprintf( guid_cstr, sizeof( guid_cstr ), "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", guid.Data1, guid.Data2, guid.Data3, guid.Data4 [ 0 ], guid.Data4 [ 1 ],
              guid.Data4 [ 2 ], guid.Data4 [ 3 ], guid.Data4 [ 4 ], guid.Data4 [ 5 ], guid.Data4 [ 6 ], guid.Data4 [ 7 ] );
    return std::string( guid_cstr );
}

const char *UTF8ToGBK( const char *strUTF8 ) {
    int    len    = MultiByteToWideChar( CP_UTF8, 0, strUTF8, -1, NULL, 0 );
    TCHAR *wszGBK = new TCHAR [ len + 1 ];
    memset( wszGBK, 0, len * 2 + 2 );
    MultiByteToWideChar( CP_UTF8, 0, strUTF8, -1, wszGBK, len );

    len         = WideCharToMultiByte( CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL );
    char *szGBK = new char [ len + 1 ];
    memset( szGBK, 0, len + 1 );
    WideCharToMultiByte( CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL );
    // std::string strTemp( szGBK );
    // delete[]szGBK;
    delete [] wszGBK;
    return szGBK;
}

char *wstring_To_UTF8( const std::wstring &str ) {
    int   nLen = ::WideCharToMultiByte( CP_UTF8, 0, str.c_str( ), -1, NULL, NULL, NULL, NULL );
    char *pBuf = new char [ nLen + 1 ];
    ::WideCharToMultiByte( CP_UTF8, 0, str.c_str( ), nLen, pBuf, nLen, NULL, NULL );
    return pBuf;
}

std::string WstringToString( const std::wstring wstr ) {
    std::string result;
    int         len = WideCharToMultiByte( CP_ACP, 0, wstr.c_str( ), wstr.size( ), NULL, 0, NULL, NULL );
    if( len <= 0 ) {
        return result;
    }

    char *buffer = new char [ len + 1 ];
    if( buffer == NULL ) {
        return result;
    }

    WideCharToMultiByte( CP_ACP, 0, wstr.c_str( ), wstr.size( ), buffer, len, NULL, NULL );
    buffer [ len ] = '\0';
    result.append( buffer );
    delete [] buffer;

    return result;
}

}   // namespace Crypto
}   // namespace Native
}   // namespace King
