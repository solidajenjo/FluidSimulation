#pragma once
#include "Module.h"

struct GLFWwindow;
class Application;

class ModuleRender : public Module
{

public:

    ModuleRender(Application* App) : Module(App) {}
    virtual ~ModuleRender() {}
    
    bool Init() override;
    bool PreUpdate() override;
    bool Update() override;
    bool PostUpdate() override;
    bool Clean() override;

    GLFWwindow* window { nullptr };
};