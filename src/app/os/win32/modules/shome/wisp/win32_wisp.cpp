/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <app/os/win32/modules/shome/wisp/win32_wisp.h>
#include "win32_wisp.h"

namespace ISpieApp
{
    namespace Platform
    {
        namespace Win32
        {
            Win32Wisp::Win32Wisp(unsigned int pid, const std::string &module_name)
                : m_wisp_info{pid, module_name}
            {
            }

            Win32Wisp::Win32Wisp(ISpieCore::Common::WispInfo wisp_info)
                : m_wisp_info(wisp_info)
            {
            }

            const ISpieCore::Common::WispInfo Win32Wisp::get_wisp_info() const
            {
                return m_wisp_info;
            }

            const unsigned int Win32Wisp::get_pid() const
            {
                return m_wisp_info.wisp_pid;
            }

            const std::string &Win32Wisp::get_image_name() const
            {
                return m_wisp_info.wisp_image_name;
            }
        }

    }
}