#pragma once
#include "Module.h"

struct GLFWwindow;

class ModuleEditor : public Module
{
public:

    ModuleEditor(GLFWwindow* window) : window(window) {};

    bool Init() override;
    bool Update() override;
    bool Clean() override;

private:

    GLFWwindow* window { nullptr };
};