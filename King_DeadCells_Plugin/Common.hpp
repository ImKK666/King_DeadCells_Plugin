#pragma once

#include "RawCommon.hpp"

#pragma warning(push)
#pragma warning(disable:4251)

#define MAKEGET(TYPE, NAME) public: TYPE NAME##();
#define MAKEGET_C(TYPE, NAME) \
  TYPE FOCUS_CLASS##::NAME##() { \
  return *reinterpret_cast< TYPE##* >( reinterpret_cast< unsigned >( this ) + static_cast< unsigned >( King::Native::ObjectAddresses::##FOCUS_CLASS##::##NAME ) ); \
  }

#define MAKEGET_REF(TYPE, NAME) public: TYPE##* NAME##();
#define MAKEGET_REF_C(TYPE, NAME) \
  TYPE##* FOCUS_CLASS##::NAME##() { \
  return reinterpret_cast< TYPE##* >( reinterpret_cast< unsigned >( this ) + static_cast< unsigned >( King::Native::ObjectAddresses::##FOCUS_CLASS##::##NAME ) ); \
  }

#define MAKEGET_STR( NAME) public: const char* NAME##();
#define MAKEGET_STR_C( NAME) \
const char* FOCUS_CLASS##::NAME##( ) { \
    unsigned ptr = reinterpret_cast< unsigned >( this ) + static_cast< unsigned >( King::Native::ObjectAddresses::##FOCUS_CLASS##::##NAME ); \
    unsigned size = *reinterpret_cast< unsigned* >( ptr + 0x10 ); \
    if ( size > 0 ) { \
        if ( size > 15 ) { \
            return  King::Native::Crypto::UTF8ToGBK( *reinterpret_cast< const char** >( ptr ) ); \
        } \
        return King::Native::Crypto::UTF8ToGBK( reinterpret_cast< const char* >( ptr ) ); \
    } \
    return "unknown"; \
}