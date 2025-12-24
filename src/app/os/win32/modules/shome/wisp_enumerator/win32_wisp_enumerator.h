#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/interfaces/wisp_enumerator_if.h>
namespace ISpieApp
{
    namespace Platform
    {
        namespace Win32
        {
            class Win32WispEnumerator : public ISpieCore::Interfaces::IWispEnumerator
            {
            protected:
                bool m_is_privileged_enumeration;
                std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> m_p_previous_snapshot;
                std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> m_p_current_snapshot;

                // craft wisp info
                ISpieCore::Common::WispInfo build_wisp_info_from_pid(unsigned int pid);

            public:
                Win32WispEnumerator(bool is_privileged_enumeration);
                virtual ~Win32WispEnumerator() = default;

                virtual std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> get_wisp_snapshot() override;
                virtual ISpieCore::Interfaces::IWispSnapshot &get_previous_wisp_snapshot() const override;
            };
        }
    }
}