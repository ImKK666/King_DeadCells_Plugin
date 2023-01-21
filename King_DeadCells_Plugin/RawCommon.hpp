#pragma once

#include "CommonDefines.hpp"

// #define KING_MANAGED_BUILD


#define GET_ABSOLUTE_M( REL ) static_cast< unsigned >( REL ) + mModuleBase
#define GET_ABSOLUTE_H( REL ) static_cast< unsigned >( REL ) + mLibhlBase


#ifdef KING_MANAGED_BUILD
 #define KING_API __declspec( dllimport )
#else
 #define KING_API __declspec( dllexport )
#endif