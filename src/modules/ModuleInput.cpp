#include "ModuleInput.h"
#include "Application.h"
#include "ModuleRender.h"
#include <iostream> //TODO: Create log systemS
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
    return glfwGetKey(App->m_render->m_window, key);
}
bool ModuleInput::IsReleased(int key) const
{
    return glfwGetKey(App->m_render->m_window, key);
}
bool ModuleInput::IsRepeted(int key) const
{
    return glfwGetKey(App->m_render->m_window, key) == GLFW_REPEAT;
}
