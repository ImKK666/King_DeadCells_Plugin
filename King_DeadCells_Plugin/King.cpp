#include "stdafx.h"

#include "Dump.hpp"

#include "ObjectManager.hpp"

#include "hl.h"
#include "Object.hpp"

DWORD WINAPI InitThread() {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONIN$", "r", stdin);
    freopen_s(&file, "CONOUT$", "w", stdout);

    spdlog::set_level(spdlog::level::trace);

    try {
        SPDLOG_INFO("Applying hook services");
        if (!King::Native::Commander::GetInstance()->ApplyHooks()) {
            SPDLOG_ERROR("Hooking Service Failed!");
        }

        SPDLOG_INFO("Applying link hooks");
        if (!King::Native::Commander::GetInstance()->LinkHooks()) {
            SPDLOG_ERROR("Link Hooks Failed!");
        }

        // Test
        {
            auto objMgr = King::Native::ObjectManager::Instance();
            printf("%p\n", objMgr);
            if (objMgr) {
                // printf( "size:%i 0:%p\n", objMgr->Size( ), objMgr->ObjectArray( ) [ 0 ] );

                King::Native::Object* LocalPlayer = nullptr;
                for (unsigned i = 0; i < objMgr->Size(); ++i) {
                    auto obj = objMgr->ObjectArray()[i];
                    if (obj->t()->kind == hl_type_kind::HOBJ) {
                        printf("[%i/%i]0x%p:%S\n", i, objMgr->Size(), obj, obj->t()->obj->name);
                        if (std::wstring(obj->t()->obj->name) == L"en.Hero") {
                            LocalPlayer = obj;
                        }
                    }
                }

                printf("-------------fields-------------\n");
                for (int i = 0; i < LocalPlayer->t()->obj->nfields; ++i) {
                    auto field = LocalPlayer->t()->obj->fields[i];
                    printf("[en.Hero][%i/%i]fields:0x%p name:%S\n", i, LocalPlayer->t()->obj->nfields, &field, field.name);
                }
            }
        }
    }
    catch (std::exception& ex) {
        ReportFatalError(nullptr, King::Native::Dump::ErrorCode::CppException, ex.what());
    }
    catch (...) {
        ReportFatalError(nullptr, King::Native::Dump::ErrorCode::CppException);
    }

    return 0;
}

LONG WINAPI Handler(EXCEPTION_POINTERS* info) {
    if (info->ExceptionRecord->ExceptionCode == 0x406D1388) {
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    {
        AddVectoredExceptionHandler(0, Handler);

        // Initial setup
        King::Native::Commander::mImageBase = reinterpret_cast<unsigned>(hModule);
        mModuleBase = reinterpret_cast<unsigned>(GetModuleHandle(NULL));
        mLibhlBase = reinterpret_cast<unsigned>(GetModuleHandle(L"libhl.dll"));

        std::thread(InitThread).detach();
    }
    case DLL_PROCESS_DETACH:
    {
        King::Native::Commander::GetInstance()->RemoveHooks();
    }
    default:
    {
        break;
    }
    }
    return TRUE;
}