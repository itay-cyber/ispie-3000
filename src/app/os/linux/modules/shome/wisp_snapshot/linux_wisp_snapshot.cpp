/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <app/os/linux/modules/shome/wisp_snapshot/linux_wisp_snapshot.h>
#include <app/os/linux/modules/shome/wisp/linux_wisp.h>

namespace ISpieApp
{
    namespace Platform
    {
        namespace Linux
        {
            ISpieCore::Interfaces::IWisp &LinuxWispSnapshot::get_wisp_by_image_name(const std::string &w_name) const
            {
                std::shared_ptr<ISpieCore::Interfaces::IWisp> ret_wisp;
                for (const auto &[wisp_pid, wisp] : m_wisp_map)
                {
                    if (wisp->get_wisp_info().wisp_image_name == w_name)
                    {
                        // found wisp
                        ret_wisp = wisp;
                        break;
                    }
                }
                return *ret_wisp;
            }

            ISpieCore::Interfaces::IWisp &LinuxWispSnapshot::get_wisp_by_pid(const unsigned int pid) const
            {
                return *m_wisp_map.at(pid);
            }

            const std::unordered_map<unsigned int, std::shared_ptr<ISpieCore::Interfaces::IWisp>> &LinuxWispSnapshot::get_all_wisps() const
            {
                return m_wisp_map;
            }

            void LinuxWispSnapshot::add_wisp(ISpieCore::Common::WispInfo wisp_info)
            {
                std::shared_ptr<ISpieCore::Interfaces::IWisp> new_wisp =
                    std::make_shared<LinuxWisp>(wisp_info);

                m_wisp_map[wisp_info.wisp_pid] = new_wisp;
            }
        }
    }
}