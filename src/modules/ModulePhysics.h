#pragma once
#include "Module.h"
#include "Math/float3.h"
#include <queue>

class Octree;
class RigidBody;

class ModulePhysics : public Module
{
public:

    ModulePhysics(Application* App);
    bool Clean() override;

    bool Update() override;

    void OnImgui() override;

    math::float3 m_OctreeSize = math::float3(15.f, 15.f, 15.f);
    bool bShowOctreeDebug = true;
    int m_MaxOctreeDepth = 5.f;
    Octree* m_Octree { nullptr };
    std::queue<RigidBody*> m_RigidBodies;

    bool bRain = false;
    float m_Timer = 0.f;
    float m_TimeBetweenRainDrops = 0.02f;
    float m_RainDropLifetime = 20.f;
    uint m_RainDropAmountPerSpawn = 5u;
};