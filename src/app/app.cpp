/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <iostream>
#include <app/app.h>

namespace ISpieApp
{
    App::App(std::unique_ptr<ISpieCore::Interfaces::IModuleMgr> p_module_mgr)
        : m_started(false), m_p_module_mgr(std::move(p_module_mgr))
    {
        std::cout << "ISpie App Constructor" << std::endl;
    }

    App::~App()
    {
        if (m_started)
        {
            // just for safety
            shutdown_app();
        }

        std::cout << "ISpie App Destructor" << std::endl;
    }

    bool App::initialize_app()
    {
        bool result = true;
        result &= m_p_module_mgr->create_modules();
        result &= m_p_module_mgr->load_modules();
        return result;
    }

    bool App::run_app()
    {
        m_started = true;
        return m_p_module_mgr->start_modules();
    }

    void App::shutdown_app()
    {
        m_started = false;
        m_p_module_mgr->stop_modules();
        m_p_module_mgr->unload_modules();
    }
}