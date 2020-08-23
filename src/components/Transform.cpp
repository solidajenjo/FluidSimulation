#include "Transform.h"
#include "Math/Quat.h"

void Transform::Update()
{
    m_Global.FromTRS(
        m_Position, 
        math::Quat::FromEulerXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z), 
        m_Scale);

    m_Front = -m_Global.Col3(2).Normalized();
	m_Up = m_Global.Col3(1).Normalized();
	m_Right = m_Global.Col3(0).Normalized();

}