#pragma once

class Application;

class Component
{

public:

    Component(Application* App) : App(App) {};
    virtual void Update() = 0;
    
    Application* App { nullptr };
};