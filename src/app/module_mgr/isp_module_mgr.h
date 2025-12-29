#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <iostream>
#include <core/interfaces/module_mgr_if.h>
#include <app/definitions.h>
#include <app/modules/shome/shome_module.h>

namespace ISpieApp
{
    class ISpieModuleMgr : public ISpieCore::Interfaces::IModuleMgr
    {
    protected:
        // map module names to module instance
        // not sure this needs to be map
        std::unordered_map<std::string, std::unique_ptr<ISpieCore::Interfaces::IModule>> m_loaded_modules;

    public:
        ISpieModuleMgr() { std::cout << "ISpieModuleMgr Constructor" << std::endl; }
        ~ISpieModuleMgr() { std::cout << "ISpieModuleMgr Destructor" << std::endl; }

        virtual bool create_modules() override;

        virtual bool load_modules() override;
        virtual void unload_modules() override;

        virtual bool start_modules() override;
        virtual void stop_modules() override;
    };
}