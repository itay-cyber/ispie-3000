#include <iostream>
#include <cstdlib>

#include <app/module_mgr/isp_module_mgr.h>
#include <app/app.h>
using namespace ISpieCore;
int main(int argc, char *argv[])
{
    std::unique_ptr<ISpieCore::Interfaces::IModuleMgr> module_mgr = std::make_unique<ISpieApp::ISpieModuleMgr>();
    ISpieApp::App app(std::move(module_mgr));

    app.initialize_app();
    app.run_app();
    app.shutdown_app();

    return 0;
}