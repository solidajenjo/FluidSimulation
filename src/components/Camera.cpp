#include "Camera.h"
#include "ModuleRender.h"

void Camera::Update()
{
	m_Frustum.type = FrustumType::PerspectiveFrustum;
    m_Frustum.projectiveSpace = FrustumSpaceGL;
    m_Frustum.handedness = FrustumRightHanded;
	m_Frustum.pos = m_Transform->m_Global.TranslatePart();
    m_Frustum.pos = float3(0, 0, -5);
	m_Frustum.front = m_Transform->m_Front;
	m_Frustum.up = m_Transform->m_Up;
	math::float3::Orthonormalize(m_Frustum.front, m_Frustum.up);
	m_Frustum.nearPlaneDistance = 1.f;
	m_Frustum.farPlaneDistance = 1000.f;
	m_Frustum.verticalFov = (90.f * math::pi / 2) / 180.f;
	m_Frustum.horizontalFov = 2.f * atanf(tanf(m_Frustum.verticalFov * 0.5f) * ModuleRender::ms_AspectRatio);
}