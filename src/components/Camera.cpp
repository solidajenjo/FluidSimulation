#include "Camera.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleInput.h"
#include "GLFW/glfw3.h"
#include "Math/Quat.h"

void Camera::UpdateFrustum()
{
	m_Frustum.type = FrustumType::PerspectiveFrustum;
    m_Frustum.projectiveSpace = FrustumSpaceGL;
    m_Frustum.handedness = FrustumRightHanded;
	m_Frustum.pos = m_Transform->m_Global.TranslatePart();
	m_Frustum.front = m_Transform->m_Front;
	m_Frustum.up = m_Transform->m_Up;
	math::float3::Orthonormalize(m_Frustum.front, m_Frustum.up);
	m_Frustum.nearPlaneDistance = .1f;
	m_Frustum.farPlaneDistance = 1000.f;
	m_Frustum.verticalFov = (90.f * math::pi / 2) / 180.f;
	m_Frustum.horizontalFov = 2.f * atanf(tanf(m_Frustum.verticalFov * 0.5f) * ModuleRender::ms_AspectRatio);
}

void Camera::UpdateInput()
{
    float mul = 1.f;
    if (App->m_input->IsPressed(GLFW_KEY_LEFT_SHIFT))
    {
        mul = 2.f;
    }
    if (App->m_input->IsPressed(GLFW_KEY_D))
    {
        m_Transform->m_Position += m_Transform->m_Right * m_Speed * mul;
    }
    if (App->m_input->IsPressed(GLFW_KEY_A))
    {
        m_Transform->m_Position -= m_Transform->m_Right * m_Speed * mul;
    }
    if (App->m_input->IsPressed(GLFW_KEY_Q))
    {
        m_Transform->m_Position += m_Transform->m_Up * m_Speed * mul;
    }
    if (App->m_input->IsPressed(GLFW_KEY_E))
    {
        m_Transform->m_Position -= m_Transform->m_Up * m_Speed * mul;
    }
    if (App->m_input->IsPressed(GLFW_KEY_W))
    {
        m_Transform->m_Position += m_Transform->m_Front * m_Speed * mul;
    }
    if (App->m_input->IsPressed(GLFW_KEY_S))
    {
        m_Transform->m_Position -= m_Transform->m_Front * m_Speed * mul;
    }
    float x,y;
    App->m_input->GetXYMouseFrameDelta(x, y);
    if (App->m_input->IsMouseButtonDown(GLFW_MOUSE_BUTTON_2))
    {
        Pitch(y * 0.01f);
        Yaw(x * 0.01f);
    }
}

void Camera::Update()
{
    m_Transform->Update();
    UpdateInput();
    UpdateFrustum();
}

void Camera::Yaw(float amount)
{

	Quat rotMat = math::Quat::RotateY(amount);
    m_Transform->m_Rotation = rotMat.Mul(m_Transform->m_Rotation);

}

void Camera::Pitch(float amount)
{

	Quat rotMat = math::Quat::RotateAxisAngle(m_Frustum.WorldRight(), amount);
	m_Transform->m_Rotation = rotMat.Mul(m_Transform->m_Rotation);

}