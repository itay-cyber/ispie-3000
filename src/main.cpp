#include <iostream>

#include <app/modules/shome/shome_module.h>

using namespace ISpieCore;
int main(int argc, char *argv[])
{
    std::unique_ptr<Interfaces::IModule> module = std::make_unique<ISpieApp::Modules::ShomeModule>();

    module->load_module();
    module->start_module();
    module->stop_module();
    module->unload_module();
    std::cout << "Module Name: " << module->get_module_name() << std::endl;
    return 0;
}