/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <iostream>
#include <app/modules/shome/shome_module.h>
#include <core/interfaces/wisp_snapshot_if.h>

namespace ISpieApp
{
    namespace Modules
    {
        ShomeModule::ShomeModule()
        {
            std::cout << "ShomeModule Constructor" << std::endl;
        }

        ShomeModule::~ShomeModule()
        {
            std::cout << "ShomeModule Destructor" << std::endl;
        }

        bool ShomeModule::load_module()
        {
            bool result = true;
#ifdef _WIN32
            // bool do_we_have_privileges = try_obtain_debug_priv();
            //  create windows platform object
            m_p_wisp_enumerator = std::make_unique<Platform::Win32::Win32WispEnumerator>(false);

#else
            // TODO: maybe dummy object?
            result = false;
            throw std::logic_error("This module hasn't been implemented for this platform");
#endif
            return result;
        }

        bool ShomeModule::start_module()
        {
            std::cout << "ShomeModule Started" << std::endl;
            std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> snapshot = m_p_wisp_enumerator->get_wisp_snapshot();

            // for now
            std::unordered_map wisps = snapshot->get_all_wisps();
            for (const auto &[wisp_id, wisp] : wisps)
            {
                std::cout << "Wisp Id: " << wisp_id << ", Wisp Image: " << wisp->get_image_name() << std::endl;
            }
            return true;
        }

        void ShomeModule::stop_module()
        {
            std::cout << "ShomeModule Stopped" << std::endl;
        }

        void ShomeModule::unload_module()
        {
            std::cout << "ShomeModule Unloaded" << std::endl;
        }

        std::string &ShomeModule::get_module_name() const
        {
            static std::string name = "ShomeModule";
            return name;
        }
#ifdef _WIN32
        bool ShomeModule::try_obtain_debug_priv()
        {
            bool result = true;
            HANDLE hToken = nullptr;

            result &= OpenProcessToken(
                          GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                          &hToken) == 0;

            LUID luid;

            result &= LookupPrivilegeValue(
                          nullptr,
                          SE_DEBUG_NAME,
                          &luid) == 0;

            // enable debug priv
            TOKEN_PRIVILEGES tp{};
            tp.PrivilegeCount = 1;
            tp.Privileges[0].Luid = luid;
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            result &= AdjustTokenPrivileges(
                          hToken,
                          FALSE,
                          &tp,
                          sizeof(tp),
                          nullptr,
                          nullptr) == 0;

            result &= GetLastError() == ERROR_NOT_ALL_ASSIGNED;

            CloseHandle(hToken);

            if (!result)
            {
                std::cout << "Shome: WARNING: running without SE_DEBUG_PRIVILEGE, process data limited" << std::endl;
            }
            return result;
        }
#endif
    }
}
