#pragma once
#define _VERSION "1.22.2"

namespace King {
namespace Native {
namespace Addresses {

enum class Globals : unsigned {
    hl_bytes_compare16 = 0x175E0,
};

enum class ObjectManager : unsigned {
    ObjectManager_Instance = 0x48184,
};

}   // namespace Addresses
}   // namespace Native
}   // namespace King