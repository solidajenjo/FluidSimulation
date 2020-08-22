#pragma once

class Application;

class Module
{
public:

    Module(Application* App) : App(App) {}

    virtual bool Init() {return true;}
    virtual bool PreUpdate() {return true;}
    virtual bool Update() {return true;}
    virtual bool PostUpdate() {return true;}
    virtual bool Clean() {return true;}
    virtual void OnImgui() {}

    Application* App { nullptr };
};