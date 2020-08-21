#pragma once
#include "Module.h"

struct GLFWwindow;

class ModuleRender : public Module
{

public:

    bool Init() override;
    bool PreUpdate() override;
    bool Update() override;
    bool PostUpdate() override;
    bool Clean() override;

    GLFWwindow* window { nullptr };
};