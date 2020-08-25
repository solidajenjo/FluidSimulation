#include "Application.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"
#include "ModuleDebugDraw.h"

bool Application::Init()
{
    bool ok = true;

    m_modules.push_back(m_render = new ModuleRender(this));
    ok = ok && m_render->Init(); //Pre initialization needed by other modules
    m_modules.push_back(new ModuleDebugDraw(this));
    m_modules.push_back(m_editor = new ModuleEditor(this));
    m_modules.push_back(m_input = new ModuleInput(this));

    for (auto& module : m_modules)
    {
        if (module != m_render)
            ok = ok && module->Init();
    }

    return ok;
}

bool Application::Update()
{
    bool ok = true;
    for (auto& module : m_modules)
    {
        ok = ok && module->PreUpdate();
    }

    for (auto& module : m_modules)
    {
        ok = ok && module->Update();
    }

    for (auto& module : m_modules)
    {
        ok = ok && module->PostUpdate();
    }
    return ok;
}

bool Application::Clean()
{
    bool ok = true;
    for (auto& module : m_modules)
    {
        ok = ok && module->Clean();
        delete module;
    }
    return ok;
}