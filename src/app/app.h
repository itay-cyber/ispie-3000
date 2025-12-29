#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <memory>
#include <core/interfaces/app_if.h>
#include <core/interfaces/module_mgr_if.h>
#include <app/module_mgr/isp_module_mgr.h>

namespace ISpieApp
{
    /*
        Main Application class
        This class just runs the app, uses modulemgr to manage modules
    */
    class App : public ISpieCore::Interfaces::IApp
    {
    protected:
        bool m_started;
        std::unique_ptr<ISpieCore::Interfaces::IModuleMgr> m_p_module_mgr;

    public:
        App(std::unique_ptr<ISpieCore::Interfaces::IModuleMgr> module_mgr);
        ~App();

        virtual bool initialize_app() override;
        virtual void shutdown_app();

        virtual bool run_app();
    };
}