#pragma once
#include <memory>

#include <spdlog/spdlog.h>

namespace King {
namespace Native {
class HookManager;

class Commander {

private:
    static std::shared_ptr< Commander > Instance;

    std::shared_ptr< spdlog::logger > mLogger;
    std::shared_ptr< HookManager > mHookManager;

public:
    static unsigned mImageBase;

    Commander( );

    std::shared_ptr< spdlog::logger > get_logger( ) const;
    std::shared_ptr< HookManager > get_hookManager( ) const;


    bool ApplyHooks( ) const;
    bool RemoveHooks( ) const;
    bool LinkHooks( ) const;

    static std::shared_ptr< Commander > GetInstance( );
};

}   // namespace Native
}   // namespace King