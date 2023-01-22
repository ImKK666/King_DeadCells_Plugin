#pragma once

namespace King {
namespace Native {
namespace ObjectAddresses {
//--------------------------------------------//
enum class ObjectManager : unsigned {   // new
    Size        = 0x4,
    ObjectArray = Size + 0x4,

    ArrayStart  = 0x10,
};

enum class Object : unsigned {   // new
    t = 0x0,
};

};   // namespace ObjectAddresses
}   // namespace Native
}   // namespace King
