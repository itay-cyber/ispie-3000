#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/interfaces/module_if.h>
#include <core/interfaces/wisp_enumerator_if.h>
#include <core/interfaces/wisp_if.h>
#include <core/interfaces/wisp_snapshot_if.h>

#ifdef _WIN32
#include <windows.h>
#include <app/os/win32/modules/shome/wisp_enumerator/win32_wisp_enumerator.h>
#else
#endif

namespace ISpieApp
{
    namespace Modules
    {
        class ShomeModule : public ISpieCore::Interfaces::IModule
        {
        protected:
            std::unique_ptr<ISpieCore::Interfaces::IWispEnumerator> m_p_wisp_enumerator;

#ifdef _WIN32
            bool try_obtain_debug_priv();
#endif
        public:
            ShomeModule();
            ~ShomeModule() override;

            // load and unload the module
            bool load_module() override;
            void unload_module() override;

            // start and stop the module's main functionality
            bool start_module() override;
            void stop_module() override;

            // get module name
            std::string &get_module_name() const override;
        };
    }
}