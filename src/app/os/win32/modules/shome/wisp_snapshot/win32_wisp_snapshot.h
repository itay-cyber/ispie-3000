#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/interfaces/wisp_snapshot_if.h>

namespace ISpieApp
{
    namespace Platform
    {
        namespace Win32
        {
            class Win32WispSnapshot : public ISpieCore::Interfaces::IWispSnapshot
            {
            protected:
                // internal map of wisps
                std::unordered_map<unsigned int, std::shared_ptr<ISpieCore::Interfaces::IWisp>> m_wisp_map;

            public:
                Win32WispSnapshot() = default;
                virtual ~Win32WispSnapshot() = default;

                virtual ISpieCore::Interfaces::IWisp &get_wisp_by_image_name(const std::string &w_name) const override;
                virtual ISpieCore::Interfaces::IWisp &get_wisp_by_pid(const unsigned int pid) const override;

                virtual const std::unordered_map<unsigned int, std::shared_ptr<ISpieCore::Interfaces::IWisp>> &get_all_wisps() const override;
                virtual void add_wisp(ISpieCore::Common::WispInfo wisp) override;
            };
        }
    }
}