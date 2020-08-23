#pragma once

class Application;

class Component
{

public:

    Component(Application* App) {};
    virtual void Update() = 0;
    
    Application* App { nullptr };
};