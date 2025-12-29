/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <app/module_mgr/isp_module_mgr.h>

namespace ISpieApp
{
    // create all the modules!!
    bool ISpieModuleMgr::create_modules()
    {
        bool result = true;

        // SHOME
        m_loaded_modules[ISpieApp::Definitions::SHOME_MODULE_NAME] = std::make_unique<ISpieApp::Modules::ShomeModule>();

        return result;
    }

    bool ISpieModuleMgr::load_modules()
    {
        bool result = true;
        for (const auto &[module_name, module_ptr] : m_loaded_modules)
        {
            result &= module_ptr->load_module();
        }
        return result;
    }

    void ISpieModuleMgr::unload_modules()
    {
        for (const auto &[module_name, module_ptr] : m_loaded_modules)
        {
            module_ptr->unload_module();
        }
    }

    bool ISpieModuleMgr::start_modules()
    {
        bool result = true;
        for (const auto &[module_name, module_ptr] : m_loaded_modules)
        {
            result &= module_ptr->start_module();
        }
        return result;
    }

    void ISpieModuleMgr::stop_modules()
    {
        for (const auto &[module_name, module_ptr] : m_loaded_modules)
        {
            module_ptr->stop_module();
        }
    }
}
