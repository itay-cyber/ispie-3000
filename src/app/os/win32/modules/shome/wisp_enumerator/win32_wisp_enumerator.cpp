/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#ifdef _WIN32 // windows specific predefined macro

// Windows specific headers
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <Psapi.h>
#include <winnt.h>

#include <core/common/types.h>
#include <core/common/utility.h>
#include <app/os/win32/modules/shome/wisp_enumerator/win32_wisp_enumerator.h>
#include <app/os/win32/modules/shome/wisp_snapshot/win32_wisp_snapshot.h>
#include "win32_wisp_enumerator.h"

namespace ISpieApp
{
    namespace Platform
    {
        namespace Win32
        {
            Win32WispEnumerator::Win32WispEnumerator(bool is_privileged_enumeration)
                : m_is_privileged_enumeration(is_privileged_enumeration)
            {
            }

            ISpieCore::Common::WispInfo Win32WispEnumerator::build_wisp_info_from_pid(unsigned int pid)
            {
                ISpieCore::Common::WispInfo new_wisp_info;
                new_wisp_info.wisp_pid = pid;

                TCHAR processName[MAX_PATH] = TEXT("<unknown>");

                // Get a handle to the process.
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                                  PROCESS_VM_READ,
                                              FALSE, pid);

                // Get the process name.
                if (NULL != hProcess)
                {
                    // this is essentially the image of the process
                    HMODULE hProcessModule;
                    DWORD cbNeeded;

                    if (EnumProcessModules(hProcess, &hProcessModule, sizeof(hProcessModule),
                                           &cbNeeded))
                    {
                        GetModuleBaseName(hProcess, hProcessModule, processName,
                                          sizeof(processName) / sizeof(TCHAR));
                    }
                }
                CloseHandle(hProcess);

                // Release the handle to the process.
                std::basic_string<TCHAR> processName_wstr(processName);
                std::string processName_str = ISpieCore::Common::wstring_to_string(processName_wstr);

                new_wisp_info.wisp_image_name = processName_str;
                return new_wisp_info;
            }

            std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> Win32WispEnumerator::get_wisp_snapshot()
            {
                DWORD aProcessesArr[1024],
                    cbNeeded, cProcesses;
                unsigned int i;

                if (!EnumProcesses(aProcessesArr, sizeof(aProcessesArr), &cbNeeded))
                {
                    // enum processes failed for some reason
                    throw std::runtime_error("Call to WAPI function EnumProcesses failed");
                }

                // Calculate how many process identifiers were returned.
                cProcesses = cbNeeded / sizeof(DWORD);

                ISpieCore::Common::WispInfo temp_winfo;
                std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> new_snapshot = std::make_shared<Win32WispSnapshot>();

                m_p_previous_snapshot = m_p_current_snapshot;

                for (i = 0; i < cProcesses; i++)
                {
                    if (aProcessesArr[i] != 0)
                    {
                        // add wisp to snapshot
                        temp_winfo = build_wisp_info_from_pid(aProcessesArr[i]);
                        new_snapshot->add_wisp(temp_winfo);
                    }
                }

                return new_snapshot;
            }

            ISpieCore::Interfaces::IWispSnapshot &Win32WispEnumerator::get_previous_wisp_snapshot() const
            {
                return *m_p_previous_snapshot;
            }
        }
    }
}

#endif