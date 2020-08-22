#pragma once
#include "Module.h"

class ModuleInput : public Module
{
public:
    ModuleInput(Application* App) : Module(App) {}

    bool PreUpdate() override;

    bool IsPressed(int key) const;
    bool IsReleased(int key) const;
    bool IsRepeted(int key) const;

private:
};