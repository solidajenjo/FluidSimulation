#pragma once
#include "Math/float3.h"

class Transform;
class AABB;
class Octree;

#define GRAVITY 8.9f

class RigidBody
{
public:

    RigidBody(const math::float3& position);
    ~RigidBody();

    math::AABB* m_AABB { nullptr };
    Transform* m_Transform { nullptr };
    bool bUseGravity = true;
    float m_Bounciness  = .85f;
    float m_LinearDrag  = .98f;
    float m_LifeTime    = .0f;
    math::float3 m_LinearVelocity = math::float3::zero;

    void Update(float deltaTime, const Octree* octree);
};