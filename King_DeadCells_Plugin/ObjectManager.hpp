#pragma once

#include "Common.hpp"

namespace King {
namespace Native {
class Object;

class KING_API ObjectManager final {
    MAKEGET( unsigned, Size )
    MAKEGET( Object **, ObjectArray )

public:
    static ObjectManager *Instance( );
};

}   // namespace Native
}   // namespace King