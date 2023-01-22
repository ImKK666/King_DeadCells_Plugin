#pragma once

#include "CommonDefines.hpp"

#define VIRTUAL_MEMORY_MIN             0x10000
#define VIRTUAL_MEMORY_MAX64           0x7FFFFFFE0000
#define IsUserVirtualMemory( Address ) ( ( ( ULONG64 ) ( Address ) ) >= VIRTUAL_MEMORY_MIN && ( ( ULONG64 ) ( Address ) ) <= VIRTUAL_MEMORY_MAX64 )


#define GET_ABSOLUTE_M( REL ) static_cast< unsigned >( REL ) + mModuleBase
#define GET_ABSOLUTE_H( REL ) static_cast< unsigned >( REL ) + mLibhlBase


// #define KING_MANAGED_BUILD
#ifdef KING_MANAGED_BUILD
 #define KING_API __declspec( dllimport )
#else
 #define KING_API __declspec( dllexport )
#endif