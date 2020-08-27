#pragma once
#include "Component.h"
#include "Math/float3.h"
#include "Math/Quat.h"
#include "Math/float4x4.h"

class Transform : public Component
{

public:

    Transform() : Component(nullptr) {}
    Transform(Application* App) : Component(App) {}

    void Update() override;

    math::float3 m_Position = math::float3::zero;
    math::Quat   m_Rotation = math::Quat::identity;
    math::float3 m_Scale    = math::float3::one;

    math::float4x4  m_Global    = math::float4x4::identity;
    math::float3    m_Front     = -m_Global.Col3(2);
	math::float3    m_Up        = m_Global.Col3(1);
	math::float3    m_Right     = m_Global.Col3(0);
};