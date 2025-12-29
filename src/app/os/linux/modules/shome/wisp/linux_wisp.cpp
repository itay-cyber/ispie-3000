/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <app/os/linux/modules/shome/wisp/linux_wisp.h>

namespace ISpieApp
{
    namespace Platform
    {
        namespace Linux
        {
            LinuxWisp::LinuxWisp(unsigned int pid, const std::string &module_name)
                : m_wisp_info{pid, module_name}
            {
            }

            LinuxWisp::LinuxWisp(ISpieCore::Common::WispInfo wisp_info)
                : m_wisp_info(wisp_info)
            {
            }

            const ISpieCore::Common::WispInfo LinuxWisp::get_wisp_info() const
            {
                return m_wisp_info;
            }

            const unsigned int LinuxWisp::get_pid() const
            {
                return m_wisp_info.wisp_pid;
            }

            const std::string &LinuxWisp::get_image_name() const
            {
                return m_wisp_info.wisp_image_name;
            }
        }

    }
}