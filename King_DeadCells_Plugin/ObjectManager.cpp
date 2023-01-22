#include "stdafx.h"

#include "ObjectManager.hpp"

namespace King {
namespace Native {

#define FOCUS_CLASS ObjectManager
MAKEGET_C( unsigned, Size )
#undef FOCUS_CLASS

ObjectManager *ObjectManager::Instance( ) {
    unsigned ptr = *reinterpret_cast< unsigned * >( GET_ABSOLUTE_H( Addresses::ObjectManager::ObjectManager_Instance ) );
    if( IsUserVirtualMemory( ptr ) ) {
        ptr = *reinterpret_cast< unsigned * >( ptr + 0x100 );
        if( IsUserVirtualMemory( ptr ) ) {
            ptr = *reinterpret_cast< unsigned * >( ptr + 0x8 );
            if( IsUserVirtualMemory( ptr ) ) {
                ptr = *reinterpret_cast< unsigned * >( ptr + 0x60 );
                if( IsUserVirtualMemory( ptr ) ) {
                    ptr = *reinterpret_cast< unsigned * >( ptr + 0x28 );
                    if( IsUserVirtualMemory( ptr ) ) {
                        ptr = *reinterpret_cast< unsigned * >( ptr + 0x90 );
                        if( IsUserVirtualMemory( ptr ) ) {
                            ptr = *reinterpret_cast< unsigned * >( ptr + 0x68 );
                            if( IsUserVirtualMemory( ptr ) ) {
                                ptr = *reinterpret_cast< unsigned * >( ptr + 0x7C );
                                if( IsUserVirtualMemory( ptr ) ) {
                                    return reinterpret_cast< ObjectManager * >( ptr );
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return nullptr;
}

Object **ObjectManager::ObjectArray( ) {
    if( !Size( ) ) {
        return nullptr;
    }

    unsigned ptr = *reinterpret_cast< unsigned * >( reinterpret_cast< unsigned >( this ) + static_cast< unsigned >( ObjectAddresses::ObjectManager::ObjectArray ) );
    return reinterpret_cast< Object ** >( ptr + static_cast< unsigned >( ObjectAddresses::ObjectManager::ArrayStart ) );
}

}   // namespace Native
}   // namespace King
