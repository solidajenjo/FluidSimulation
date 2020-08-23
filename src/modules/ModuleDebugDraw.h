#pragma once

#include "Module.h"

class DDRenderInterfaceCoreGL;
class Application;

class ModuleDebugDraw : public Module
{

public:

    ModuleDebugDraw(Application* App) : Module(App) {}

	bool Init() override;
	bool Update() override;
	bool Clean() override;

    //void Draw(ComponentCamera* camera, unsigned fbo, unsigned fb_width, unsigned fb_height);
private:

    static DDRenderInterfaceCoreGL* implementation;
};

