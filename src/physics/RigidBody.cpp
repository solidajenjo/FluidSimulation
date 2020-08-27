#include "RigidBody.h"
#include "Transform.h"
#include "Geometry/AABB.h"
#include "debugdraw.h"
#include "Octree.h"
#include "Mesh.h"

RigidBody::RigidBody(const math::float3& position)
{
    m_Transform = new Transform();
    m_Transform->m_Position = position;
    m_AABB = new math::AABB();
    m_AABB->SetFromCenterAndSize(position, math::float3(.1f));
}

RigidBody::~RigidBody()
{
    delete m_Transform;
    delete m_AABB;
}

void RigidBody::Update(float deltaTime, const Octree* octree)
{
    if (bUseGravity)
    {
        m_LinearVelocity += GRAVITY * deltaTime * 0.01f * -math::float3::unitY;
    }

    m_Transform->m_Position = m_Transform->m_Position + m_LinearVelocity;
    m_Transform->Update();
    m_AABB->Translate(m_LinearVelocity);
    
    auto possibleCollisions = octree->GetPossibleCollisions(m_AABB);

    for (const TriangleData* triData : possibleCollisions)
    {
        if (m_AABB->Intersects(triData->m_Triangle))
        {
            m_LinearVelocity = triData->m_Normal * m_LinearVelocity.Length() * m_Bounciness;
        }
    }

    m_LinearVelocity *= m_LinearDrag;

    dd::point(m_Transform->m_Position, dd::colors::Blue, 5.1f);
    //dd::aabb(m_AABB->minPoint, m_AABB->maxPoint, dd::colors::Red);
}