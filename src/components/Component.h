#pragma once

class Application;

typedef unsigned uint;

class Component
{

public:

    Component(Application* App) : App(App) {};
    virtual void Update() = 0;
    
    Application* App { nullptr };
};