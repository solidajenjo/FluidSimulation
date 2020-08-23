#pragma once
#include "Module.h"
#include "Math/float4x4.h"

struct GLFWwindow;
class Application;

class ModuleRender : public Module
{

public:

    ModuleRender(Application* App) : Module(App) {}
    virtual ~ModuleRender() {}

    bool Init() override;
    bool PreUpdate() override;
    bool Update() override;
    bool PostUpdate() override;
    bool Clean() override;

    void SetViewProjectionUniform(const math::float4x4& viewProj);

    GLFWwindow* m_window { nullptr };

    int shaderProgram;unsigned int VBO, VAO;
    static int ms_width, ms_height;
    static float ms_AspectRatio;
};