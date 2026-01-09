/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <app/modules/tutor/tutor_module.h>

namespace ISpieApp
{
    namespace Modules
    {
        TutorModule::TutorModule()
        {
        }
        TutorModule::~TutorModule()
        {
        }

        bool TutorModule::load_module()
        {
            return false;
        }

        void TutorModule::unload_module()
        {
        }

        bool TutorModule::start_module()
        {
            return false;
        }

        void TutorModule::stop_module()
        {
        }

        const std::string &TutorModule::get_module_name() const
        {
            return MODULE_NAME;
        }

    }
}