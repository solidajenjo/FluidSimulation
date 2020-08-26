#include "ModulePhysics.h"
#include "Octree.h"
#include "imgui.h"
#include "debugdraw.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Mesh.h"

ModulePhysics::ModulePhysics(Application* App) : Module(App)
{
    m_Octree = new Octree();
}

bool ModulePhysics::Clean()
{
    delete m_Octree;
    return true;
}

void ModulePhysics::OnImgui()
{
    if(bShowOctreeDebug)
        dd::aabb(-m_OctreeSize, m_OctreeSize, dd::colors::LightSkyBlue);

    if (ImGui::TreeNodeEx("ModulePhysics"))
    {
        ImGui::Checkbox("Show octree", &bShowOctreeDebug);
        if (bShowOctreeDebug)
        {
            m_Octree->DebugDraw();
        }
        ImGui::DragFloat3("Octree size", &m_OctreeSize[0], 0.1f, 0.1f, 1000.f);
        if (ImGui::InputInt("Max octree depth", &m_MaxOctreeDepth))
        {
            if (m_MaxOctreeDepth < 1)
                m_MaxOctreeDepth = 1;
        }
        if (ImGui::Button("Calculate Octree"))
        {
            AABB rootAABB;
            rootAABB.SetFromCenterAndSize(math::float3::zero, m_OctreeSize);
            std::vector<Mesh*> meshes;
            meshes.push_back(App->m_Render->m_Mesh);
            m_Octree->Calculate(rootAABB, meshes, m_MaxOctreeDepth);
        }
        ImGui::TreePop();
    }
}