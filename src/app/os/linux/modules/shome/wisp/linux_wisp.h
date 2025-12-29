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
        namespace Linux
        {
            class LinuxWisp : public ISpieCore::Interfaces::IWisp
            {
            protected:
                const ISpieCore::Common::WispInfo m_wisp_info;

            public:
                LinuxWisp(unsigned int pid, const std::string &module_name);
                LinuxWisp(ISpieCore::Common::WispInfo wisp_info);
                virtual ~LinuxWisp() = default;

                virtual const ISpieCore::Common::WispInfo get_wisp_info() const override;
                virtual const unsigned int get_pid() const override;
                virtual const std::string &get_image_name() const override;
            };
        }
    }
}
