#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <string>

namespace ISpieCore
{
    namespace Interfaces
    {
        class IModule
        {
        public:
            virtual ~IModule() = default;

            // load and unload the module
            virtual bool load_module() = 0;
            virtual void unload_module() = 0;

            // start and stop the module's main functionality
            virtual bool start_module() = 0;
            virtual void stop_module() = 0;

            // get module name
            virtual std::string &get_module_name() const = 0;
        };
    }
}