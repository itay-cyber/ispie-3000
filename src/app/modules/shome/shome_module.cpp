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
            bool do_we_have_privileges = try_obtain_debug_priv();
            //  create windows platform object
            m_p_wisp_enumerator = std::make_unique<Platform::Win32::Win32WispEnumerator>(do_we_have_privileges);

#else
            // privs?
            // create linux platform object
            m_p_wisp_enumerator = std::make_unique<Platform::Linux::LinuxWispEnumerator>(true);
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

        const std::string &ShomeModule::get_module_name() const
        {
            return MODULE_NAME;
        }
#ifdef _WIN32
        bool ShomeModule::try_obtain_debug_priv()
        {
            bool result = true;
            HANDLE hToken = nullptr;
            BOOL winResult = OpenProcessToken(
                GetCurrentProcess(),
                TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                &hToken);

            result &= winResult == TRUE;

            // SE_DEBUG_NAME has a certain LUID on this machine
            // FINDING IT
            LUID luid;
            winResult = LookupPrivilegeValue(
                nullptr,
                SE_DEBUG_NAME,
                &luid);

            result &= winResult == TRUE;

            // enable debug priv
            TOKEN_PRIVILEGES tp{};
            tp.PrivilegeCount = 1;
            tp.Privileges[0].Luid = luid;
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            winResult = AdjustTokenPrivileges(
                hToken,
                FALSE,
                &tp,
                sizeof(tp),
                nullptr,
                nullptr);

            result &= winResult == TRUE;
            DWORD res = GetLastError();
            result &= res != ERROR_NOT_ALL_ASSIGNED;

            std::cout << res << std::endl;

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
