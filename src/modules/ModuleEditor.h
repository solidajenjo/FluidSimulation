#pragma once
#include "Module.h"

struct GLFWwindow;
class Application;

class ModuleEditor : public Module
{
public:

    ModuleEditor(Application* App) : Module(App) {};
    virtual ~ModuleEditor() {}

    bool Init() override;
    bool Update() override;
    bool Clean() override;

private:

    void DrawGrid();

};