#pragma once
#include "Module.h"

struct GLFWwindow;

class ModuleRender : public Module
{

public:

    bool Init() override;
    bool Update() override;
    bool Clean() override;

    GLFWwindow* window { nullptr };
};