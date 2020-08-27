#include "ModulePhysics.h"
#include "Octree.h"
#include "imgui.h"
#include "debugdraw.h"
#include "Application.h"
#include "ModuleRender.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Mesh.h"
#include <GLFW/glfw3.h>

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
        ImGui::Text("DT -> %.3f | Active RBs %d", App->m_DeltaTime, m_RigidBodies.size());
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
            math::AABB rootAABB;
            rootAABB.SetFromCenterAndSize(math::float3::zero, m_OctreeSize);
            std::vector<Mesh*> meshes;
            meshes.push_back(App->m_Render->m_Mesh);
            m_Octree->Calculate(rootAABB, meshes, m_MaxOctreeDepth);
        }
        if (ImGui::Button("Add RigidBody"))
        {
            m_RigidBodies.push(new RigidBody(math::float3(6.f, 10.f, 0.f)));
        }
        ImGui::Separator();
        ImGui::Checkbox("Rain", &bRain);
        ImGui::DragFloat("Time between rain drops", &m_TimeBetweenRainDrops);
        ImGui::TreePop();
    }
}

bool ModulePhysics::Update()
{
    if (bRain)
    {
        if (m_Timer <= 0)
        {
            m_Timer = m_TimeBetweenRainDrops;
            for (size_t i = 0; i < m_RainDropAmountPerSpawn; ++i)
            {
                float x = (float)(rand()%50) - 25.f;
                float z = (float)(rand()%50) - 25.f;
                m_RigidBodies.push(new RigidBody(math::float3(x * .1f, 5.f, z * .1f)));
            }
        }
        m_Timer -= App->m_DeltaTime;        
    }
    size_t rbAmount = m_RigidBodies.size();
    for (size_t i = 0; i < rbAmount; ++i)
    {
        RigidBody* rb = m_RigidBodies.front();
        m_RigidBodies.pop();
        rb->Update(App->m_DeltaTime, m_Octree);
        rb->m_LifeTime += App->m_DeltaTime;
        if (rb->m_LifeTime < m_RainDropLifetime)
        {
            m_RigidBodies.push(rb);
        }
    }
    return true;
}