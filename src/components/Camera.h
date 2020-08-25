#pragma once
#include "Component.h"
#include "Transform.h"
#include "Geometry/Frustum.h"

class Camera : public Component
{
public:

    Camera(Application* App) : Component(App) { m_Transform = new Transform(App); }
    virtual ~Camera() { delete m_Transform; }

    void Update() override;

    Transform* m_Transform { nullptr };
    math::Frustum m_Frustum;

    float m_Speed = 0.1f;

    void LookAt(const math::float3& target);

private:

    void UpdateInput();
    void UpdateFrustum();

    void Yaw(float amount);
    void Pitch(float amount);
};