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

    ImGui_ImplGlfw_InitForOpenGL(App->m_render->m_window, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);

    m_Camera = new Camera(App);

    return true;
}
bool ModuleEditor::Update()
{
    m_Camera->Update();
    App->m_render->SetViewProjectionUniform(m_Camera->m_Frustum.ComputeViewProjMatrix());
    DrawGrid();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    static bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return true;
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
    dd::xzSquareGrid(-100.f, 100.f, -.5f, .1f, dd::colors::Gray);
}