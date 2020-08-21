#include "Application.h"
#include "ModuleRender.h"

bool Application::Init()
{
    modules.push_back(render = new ModuleRender());

    bool ok = true;
    for (auto& module : modules)
    {
        ok = ok && module->Init();
    }

    return ok;
}

bool Application::Update()
{
    bool ok = true;
    for (auto& module : modules)
    {
        ok = ok && module->PreUpdate();
    }

    for (auto& module : modules)
    {
        ok = ok && module->Update();
    }

    for (auto& module : modules)
    {
        ok = ok && module->PostUpdate();
    }
    return ok;
}

bool Application::Clean()
{
    bool ok = true;
    for (auto& module : modules)
    {
        ok = ok && module->Clean();
    }
    return ok;
}