#include "ModuleEditor.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Application.h"
#include "ModuleRender.h"
#include "debugdraw.h"
#include "Camera.h"

bool ModuleEditor::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(App->m_Render->m_window, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);

    m_Camera = new Camera(App);
    m_Camera->m_Transform->m_Position = math::float3(0.f, 5.f, 10.f);
    m_Camera->LookAt(m_Camera->m_Transform->m_Position);
    return true;
}
bool ModuleEditor::Update()
{
    m_Camera->Update();
    DrawGrid();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("FluidSolver Control Panel");
    
    for (Module* module : App->m_Modules)
    {
        module->OnImgui();
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return true;
}
void ModuleEditor::OnImgui()
{
    if (ImGui::TreeNodeEx("ModuleEditor"))
    {
        float d = m_Camera->m_Transform->m_Up.Dot(math::float3::unitY);
        ImGui::Text("%.3f", d);
        ImGui::TreePop();
    }
}

bool ModuleEditor::Clean()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete m_Camera;
    return true;
}

void ModuleEditor::DrawGrid()
{
    dd::xzSquareGrid(-100.f, 100.f, -0.001f, 1.f, dd::colors::Gray);
    dd::axisTriad(math::float4x4::identity, 10.f, 110.f);
    dd::line(math::float3::zero, math::float3(0.f, -100.f, 0.f), dd::colors::Green);
    dd::line(math::float3::zero, math::float3(-100.f, 0.f, 0.f), dd::colors::DarkRed);
    dd::line(math::float3::zero, math::float3(0.f, 0.f, -100.f), dd::colors::DarkSlateBlue);
}