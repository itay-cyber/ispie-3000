#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/interfaces/wisp_enumerator_if.h>
#include <filesystem>

namespace ISpieApp
{
    namespace Platform
    {
        namespace Linux
        {
            namespace fs = std::filesystem;
            class LinuxWispEnumerator : public ISpieCore::Interfaces::IWispEnumerator
            {
            protected:
                std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> m_p_previous_snapshot;
                std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> m_p_current_snapshot;

                // finds the corresponding command run for this specific process pid
                ISpieCore::Common::WispInfo build_wisp_info_from_pid(unsigned int pid);

                /* checks if a specific path points to a process in proc, if yes returns the pid number,
                 if not, returns Definitions::INVALID_PIN */
                int try_get_proc_subpath_id(fs::path &path);

            public:
                LinuxWispEnumerator();
                virtual ~LinuxWispEnumerator() = default;

                virtual std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> get_wisp_snapshot() override;
                virtual ISpieCore::Interfaces::IWispSnapshot &get_previous_wisp_snapshot() const override;
            };
        }
    }
}
