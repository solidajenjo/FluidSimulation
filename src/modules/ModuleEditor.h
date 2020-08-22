#pragma once
#include "Module.h"

struct GLFWwindow;
class Application;

class ModuleEditor : public Module
{
public:

    ModuleEditor(GLFWwindow* window, Application* App) : window(window), Module(App) {};
    virtual ~ModuleEditor() {}

    bool Init() override;
    bool Update() override;
    bool Clean() override;

private:

    GLFWwindow* window { nullptr };
};