/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <app/os/win32/modules/shome/wisp_snapshot/win32_wisp_snapshot.h>
#include <app/os/win32/modules/shome/wisp/win32_wisp.h>

namespace ISpieApp
{
    namespace Platform
    {
        namespace Win32
        {
            ISpieCore::Interfaces::IWisp &Win32WispSnapshot::get_wisp_by_image_name(const std::string &w_name) const
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

            ISpieCore::Interfaces::IWisp &Win32WispSnapshot::get_wisp_by_pid(const unsigned int pid) const
            {
                return *m_wisp_map.at(pid);
            }

            const std::unordered_map<unsigned int, std::shared_ptr<ISpieCore::Interfaces::IWisp>> &Win32WispSnapshot::get_all_wisps() const
            {
                return m_wisp_map;
            }

            void Win32WispSnapshot::add_wisp(ISpieCore::Common::WispInfo wisp_info)
            {
                std::shared_ptr<ISpieCore::Interfaces::IWisp> new_wisp =
                    std::make_shared<Win32Wisp>(wisp_info);

                m_wisp_map[wisp_info.wisp_pid] = new_wisp;
            }
        }
    }
}