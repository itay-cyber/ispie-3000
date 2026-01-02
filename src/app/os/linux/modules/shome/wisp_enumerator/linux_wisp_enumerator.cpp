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
#include <fstream>

#include <core/common/types.h>
#include <core/common/utility.h>
#include <app/os/linux/modules/shome/wisp_enumerator/linux_wisp_enumerator.h>
#include <app/os/linux/modules/shome/wisp_snapshot/linux_wisp_snapshot.h>
#include <app/definitions.h>
#include <app/config.h>

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
                ISpieCore::Common::WispInfo wisp_info;
                wisp_info.wisp_pid = pid;

                std::string path_to_cmdline = "/proc/" + std::to_string(pid) + "/cmdline";
                std::ifstream cmdline_file_stream(path_to_cmdline);

                std::string module = std::string();
                std::getline(cmdline_file_stream, module);
                if (Config::TRUNCATE_MODULE_STRS)
                {
                    if (module.length() > Config::MODULE_STRS_MAX_LENGTH)
                    {
                        module = module.substr(0, Config::MODULE_STRS_MAX_LENGTH);

                        module += "...";
                    }
                }
                ISpieCore::Common::replace_chars(module, '\000', ' ');
                if (module == "")
                {
                    std::cerr << "Error reading cmdline file for " << std::to_string(pid) << std::endl;
                }
                wisp_info.wisp_image_name = module;
                return wisp_info;
            }

            int LinuxWispEnumerator::try_get_proc_subpath_id(fs::path &path)
            {
                // convert path to string
                std::string path_str = path.generic_string();
                std::string pid = std::string();
                bool started_pid_in_path = false;
                int converted_pid = Definitions::INVALID_PID;
                for (int i = 0; i < path_str.length(); i++)
                {
                    if (started_pid_in_path)
                    {
                        pid += path_str[i];
                    }
                    else if (isdigit(path_str[i]))
                    {
                        started_pid_in_path = true;
                        pid += path_str[i];
                    }
                }

                // try converting the pid found into a numerical value
                try
                {
                    if (pid != "")
                        converted_pid = std::stoi(pid);
                }
                catch (std::invalid_argument &e)
                {
                    std::cerr << "Error occurred: couldn't convert to int" << std::endl;
                }

                return converted_pid;
            }

            std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> LinuxWispEnumerator::get_wisp_snapshot()
            {
                ISpieCore::Common::WispInfo temp;
                int proc_pid = Definitions::INVALID_PID;
                fs::path entry_path;

                m_p_previous_snapshot = m_p_current_snapshot;

                std::shared_ptr<ISpieCore::Interfaces::IWispSnapshot> p_new_snapshot = std::make_shared<LinuxWispSnapshot>();

                // iterate /proc for pids
                for (const auto &entry : fs::directory_iterator("/proc"))
                {
                    entry_path = entry.path();
                    proc_pid = try_get_proc_subpath_id(entry_path);
                    if (proc_pid != Definitions::INVALID_PID)
                    {
                        // make wisp and add it to snapshot
                        temp = build_wisp_info_from_pid(proc_pid);
                        p_new_snapshot->add_wisp(temp);
                    }
                }
                m_p_current_snapshot = p_new_snapshot;
                return p_new_snapshot;
            }

            ISpieCore::Interfaces::IWispSnapshot &LinuxWispEnumerator::get_previous_wisp_snapshot() const
            {
                ISpieCore::Interfaces::IWispSnapshot &d = *m_p_previous_snapshot;
                return d;
            }
        }
    }
}

#endif