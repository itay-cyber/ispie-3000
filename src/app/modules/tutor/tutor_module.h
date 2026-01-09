#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/interfaces/module_if.h>
#include <app/definitions.h>
namespace ISpieApp
{
    namespace Modules
    {
        class TutorModule : public ISpieCore::Interfaces::IModule
        {
        protected:
            const std::string MODULE_NAME = ISpieApp::Definitions::TUTOR_MODULE_NAME;

        public:
            TutorModule();
            ~TutorModule() override;

            bool load_module() override;
            void unload_module() override;

            // start and stop the module's main functionality
            bool start_module() override;
            void stop_module() override;

            // get module name
            const std::string &get_module_name() const override;
        };
    }
}