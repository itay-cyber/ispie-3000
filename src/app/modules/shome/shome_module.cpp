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
            : m_privileged_enum(false)
        {
        }

        ShomeModule::~ShomeModule()
        {
        }

        bool ShomeModule::load_module()
        {
            bool result = true;
#ifdef _WIN32
            bool do_we_have_privileges = try_obtain_debug_priv();
            m_privileged_enum = do_we_have_privileges;
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
            bool result = true;
            // for now
            if (snapshot)
            {
                std::unordered_map<unsigned int, std::shared_ptr<ISpieCore::Interfaces::IWisp>> wisps = snapshot->get_all_wisps();
                if (!wisps.empty())
                {
                    for (const auto &[wisp_id, wisp] : wisps)
                    {
                        // TODO: Replace with PrettyLogger class in the future
                        std::string strwispid = std::to_string(wisp_id);
                        std::size_t len = strwispid.length();
                        for (int i = 0; i < 5 - len; i++)
                        {
                            strwispid += ' ';
                        }
                        std::cout << strwispid << "       " << wisp->get_image_name() << std::endl;
                    }
                }
                else
                {
                    result = false;
                }
            }
            return result;
        }

        void ShomeModule::stop_module()
        {
            std::cout << "ShomeModule Stopped" << std::endl;
        }

        void ShomeModule::unload_module()
        {
            if (m_privileged_enum)
            {
                disable_debug_priv();
            }
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

            CloseHandle(hToken);

            if (!result)
            {
                std::cout << "Shome: WARNING: running without SE_DEBUG_PRIVILEGE, process data limited" << std::endl;
            }
            return result;
        }

        bool ShomeModule::disable_debug_priv()
        {
            bool result = true;
            // get a handle to the process access token
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
            // passing 0 disables this
            tp.Privileges[0].Attributes = 0;

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

            CloseHandle(hToken);

            if (!result)
            {
                std::cout << "Shome: WARNING: failed to disable SE_DEBUG_PRIV after use" << std::endl;
            }
            return result;
        }
#endif
    }
}
