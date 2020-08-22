#include "ModuleInput.h"
#include "Application.h"
#include "ModuleRender.h"
#include "GLFW/glfw3.h"

bool ModuleInput::PreUpdate()
{
    glfwPollEvents();
    if(glfwGetKey(App->m_render->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(App->m_render->m_window, true);
    
    return true; 
}


bool ModuleInput::IsPressed(int key) const
{
    return glfwGetKey(App->m_render->m_window, key) == GLFW_PRESS;
}
bool ModuleInput::IsReleased(int key) const
{
    return glfwGetKey(App->m_render->m_window, key) == GLFW_RELEASE;
}
bool ModuleInput::IsRepeted(int key) const
{
    return glfwGetKey(App->m_render->m_window, key) == GLFW_REPEAT;
}
