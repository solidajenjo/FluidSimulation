#pragma once
#include "Module.h"

class ModuleInput : public Module
{
public:
    ModuleInput(Application* App) : Module(App) {}

    bool PreUpdate() override;

    bool IsPressed(int key) const;
    bool IsReleased(int key) const;
    bool IsMouseButtonDown(int button) const;
    
    void GetXYMouseFrameDelta(float& x, float& y);


private:

    float m_LastX = 0.f, m_LastY = 0.f;
};