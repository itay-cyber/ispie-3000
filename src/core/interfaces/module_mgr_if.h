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
        class IModuleMgr
        {
            // pure virtual
        public:
            virtual ~IModuleMgr() = default;
            virtual bool create_modules() = 0;

            virtual bool load_modules() = 0;
            virtual void unload_modules() = 0;

            virtual bool start_modules() = 0;
            virtual void stop_modules() = 0;
        };
    }
}