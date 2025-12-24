#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/interfaces/wisp_if.h>
namespace ISpieApp
{
    namespace Platform
    {
        namespace Win32
        {
            class Win32Wisp : public ISpieCore::Interfaces::IWisp
            {
            protected:
                const ISpieCore::Common::WispInfo m_wisp_info;

            public:
                Win32Wisp(unsigned int pid, const std::string &module_name);
                Win32Wisp(ISpieCore::Common::WispInfo wisp_info);
                virtual ~Win32Wisp() = default;

                virtual const ISpieCore::Common::WispInfo get_wisp_info() const override;
                virtual const unsigned int get_pid() const override;
                virtual const std::string &get_image_name() const override;
            };
        }
    }
}
