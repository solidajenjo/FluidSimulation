#include "ModuleInput.h"
#include "Application.h"
#include "ModuleRender.h"
#include <iostream> //TODO: Create log systemS
#include "GLFW/glfw3.h"

bool ModuleInput::PreUpdate()
{
    glfwPollEvents();
    if(glfwGetKey(App->m_Render->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(App->m_Render->m_window, true);
    
    return true; 
}

bool ModuleInput::IsMouseButtonDown(int button) const
{
    return glfwGetMouseButton(App->m_Render->m_window, button);
}
bool ModuleInput::IsPressed(int key) const
{
    return glfwGetKey(App->m_Render->m_window, key);
}
bool ModuleInput::IsReleased(int key) const
{
    return glfwGetKey(App->m_Render->m_window, key);
}

void ModuleInput::GetXYMouseFrameDelta(float& x, float& y) 
{
    double xpos, ypos;
    glfwGetCursorPos(App->m_Render->m_window, &xpos, &ypos);
    x = m_LastX - xpos;
    y = m_LastY - ypos;
    m_LastX = xpos;
    m_LastY = ypos;
}