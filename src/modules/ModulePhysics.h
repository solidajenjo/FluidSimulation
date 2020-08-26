#pragma once
#include "Module.h"
#include "Math/float3.h"

class Octree;

class ModulePhysics : public Module
{
public:

    ModulePhysics(Application* App);
    bool Clean() override;

    void OnImgui() override;

    math::float3 m_OctreeSize = math::float3(15.f, 15.f, 15.f);
    bool bShowOctreeDebug = true;
    int m_MaxOctreeDepth = 5.f;
    Octree* m_Octree { nullptr };
};