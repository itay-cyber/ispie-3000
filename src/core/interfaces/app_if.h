#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/

namespace ISpieCore
{
    namespace Interfaces
    {
        class IApp
        {
            // purely virtual

        public:
            virtual ~IApp() = default;

            virtual bool initialize_app() = 0;
            virtual void shutdown_app() = 0;

            virtual bool run_app() = 0;
        };
    }
}