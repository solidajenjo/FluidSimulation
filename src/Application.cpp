#include "Application.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"

bool Application::Init()
{
    modules.push_back(render = new ModuleRender());
    render->Init();
    modules.push_back(editor = new ModuleEditor(render->window));

    bool ok = true;
    for (auto& module : modules)
    {
        if (module != render)
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