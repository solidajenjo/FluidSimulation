#include "Application.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"
#include "ModuleDebugDraw.h"
#include "ModulePhysics.h"

bool Application::Init()
{
    bool ok = true;

    m_Modules.push_back(m_Render = new ModuleRender(this));
    ok = ok && m_Render->Init(); //Pre initialization needed by other modules
    m_Modules.push_back(new ModuleDebugDraw(this));
    m_Modules.push_back(m_Editor = new ModuleEditor(this));
    m_Modules.push_back(m_Input = new ModuleInput(this));
    m_Modules.push_back(m_Physics = new ModulePhysics(this));

    for (auto& module : m_Modules)
    {
        if (module != m_Render)
            ok = ok && module->Init();
    }

    return ok;
}

bool Application::Update()
{
    bool ok = true;
    for (auto& module : m_Modules)
    {
        ok = ok && module->PreUpdate();
    }

    for (auto& module : m_Modules)
    {
        ok = ok && module->Update();
    }

    for (auto& module : m_Modules)
    {
        ok = ok && module->PostUpdate();
    }
    return ok;
}

bool Application::Clean()
{
    bool ok = true;
    for (auto& module : m_Modules)
    {
        ok = ok && module->Clean();
        delete module;
    }
    return ok;
}