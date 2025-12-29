/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#ifndef _WIN32 // windows specific predefined macro

// Linux specific headers
#include <iostream>

#include <core/common/types.h>
#include <core/common/utility.h>
#include <app/os/linux/modules/shome/wisp_enumerator/linux_wisp_enumerator.h>
#include <app/os/linux/modules/shome/wisp_snapshot/linux_wisp_snapshot.h>

namespace ISpieApp
{
    namespace Platform
    {
        namespace Linux
        {
            LinuxWispEnumerator::LinuxWispEnumerator(bool is_privileged_enumeration)
                : m_is_privileged_enumeration(is_privileged_enumeration)
            {
            }

            ISpieCore::Common::WispInfo LinuxWispEnumerator::build_wisp_info_from_pid(unsigned int pid)
            {
            }

            std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> LinuxWispEnumerator::get_wisp_snapshot()
            {
            }

            ISpieCore::Interfaces::IWispSnapshot &LinuxWispEnumerator::get_previous_wisp_snapshot() const
            {
            }
        }
    }
}

#endif