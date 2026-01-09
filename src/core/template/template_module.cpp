/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/template/template_module.h>

namespace ISpieApp
{
    namespace Modules
    {
        TemplateModule::TemplateModule()
        {
        }
        TemplateModule::~TemplateModule()
        {
        }

        bool TemplateModule::load_module()
        {
            return false;
        }

        void TemplateModule::unload_module()
        {
        }

        bool TemplateModule::start_module()
        {
            return false;
        }

        void TemplateModule::stop_module()
        {
        }

        const std::string &TemplateModule::get_module_name() const
        {
            return MODULE_NAME;
        }

    }
}