#pragma once
#include "Module.h"

struct GLFWwindow;
class Application;
class Camera;

class ModuleEditor : public Module
{
public:

    ModuleEditor(Application* App) : Module(App) {};
    virtual ~ModuleEditor() {}

    bool Init() override;
    bool Update() override;
    bool Clean() override;
    void OnImgui() override;

    Camera* m_Camera { nullptr };
    
private:

    void DrawGrid();

};