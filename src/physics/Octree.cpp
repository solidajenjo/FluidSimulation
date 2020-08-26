#include "Octree.h"
#include "Mesh.h"
#include <queue>
#include <iostream>
#include "debugdraw.h"

Node::Node()
{
    m_AABB = new AABB(); //TODO: Create a AABB pool to ensure cache friendly
}

Node::Node(const math::float3& pos, const math::float3& size, uint depth)
{
	m_Depth = depth + 1;
    m_AABB = new AABB();
	m_AABB->SetFromCenterAndSize(pos, size);
}
Node::~Node()
{
    delete m_AABB;
    //TODO: delete childs
}
void Node::Flush()
{
    bool shouldDivide = true;
	math::float3 center = m_AABB->CenterPoint();
	math::float3 newSize = m_AABB->Size();
	newSize *= .5f;
    /*
    ---    --+    -+-    -++
    +--    +-+    ++-    +++
    */
    m_LowerNodes.clear();

    for (const TriangleData* triData : m_Bucket)
    {
        if (m_AABB->Contains(triData->m_Triangle)
            || m_AABB->Intersects(triData->m_Triangle))
        {
            if (shouldDivide)
            {
                shouldDivide = false;
                m_LowerNodes.push_back(new Node(math::float3(center.x - newSize.x * .5f, center.y - newSize.y * .5f, 
                    center.z - newSize.z * .5f), newSize, m_Depth));
                m_LowerNodes.push_back(new Node(math::float3(center.x - newSize.x * .5f, center.y - newSize.y * .5f, 
                    center.z + newSize.z * .5f), newSize, m_Depth));
                m_LowerNodes.push_back(new Node(math::float3(center.x - newSize.x * .5f, center.y + newSize.y * .5f, 
                    center.z - newSize.z * .5f), newSize, m_Depth));
                m_LowerNodes.push_back(new Node(math::float3(center.x - newSize.x * .5f, center.y + newSize.y * .5f, 
                    center.z + newSize.z * .5f), newSize, m_Depth));
                m_LowerNodes.push_back(new Node(math::float3(center.x + newSize.x * .5f, center.y - newSize.y * .5f, 
                    center.z - newSize.z * .5f), newSize, m_Depth));
                m_LowerNodes.push_back(new Node(math::float3(center.x + newSize.x * .5f, center.y - newSize.y * .5f, 
                    center.z + newSize.z * .5f), newSize, m_Depth));
                m_LowerNodes.push_back(new Node(math::float3(center.x + newSize.x * .5f, center.y + newSize.y * .5f, 
                    center.z - newSize.z * .5f), newSize, m_Depth));
                m_LowerNodes.push_back(new Node(math::float3(center.x + newSize.x * .5f, center.y + newSize.y * .5f, 
                    center.z + newSize.z * .5f), newSize, m_Depth));
            }
            for (Node* lowNode : m_LowerNodes)
            {
                if (lowNode->m_AABB->Contains(triData->m_Triangle)
                    || lowNode->m_AABB->Intersects(triData->m_Triangle))
                {
                    lowNode->m_Bucket.push_back(triData);
                }
            }
        }
    }
    m_Bucket.clear();
}

void Octree::Calculate(const AABB& rootAABB, const std::vector<Mesh*>& meshes, uint maxDepth)
{
    std::queue<Node*> Q;
    if (m_Root)
    {
        delete m_Root;
    }
    m_Root = new Node();
    m_Root->m_AABB->SetFromCenterAndSize(math::float3::zero, rootAABB.Size());

    for (const Mesh* mesh : meshes)
    {
        for (const TriangleData& triData : mesh->m_Triangles)
        {
            m_Root->m_Bucket.push_back(&triData);
        }
    }
    Q.push(m_Root);

    while (!Q.empty())
    {
        Node* currentNode = Q.front();
        Q.pop();
 
        if (currentNode->m_Depth < maxDepth)
        {
            currentNode->Flush();
            for (Node* newNode : currentNode->m_LowerNodes)
            {
                Q.push(newNode);
            }
        }        
    }
}

Octree::~Octree()
{
    //delete with stack traverse
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "hla";
    }
}

void Octree::DebugDraw()
{
    std::queue<Node*> Q;
    if (!m_Root)
    {
        return;
    }
    
    Q.push(m_Root);

    while (!Q.empty())
    {
        Node* currentNode = Q.front();
        Q.pop();
    
        if (!currentNode->m_Bucket.empty() && currentNode->m_LowerNodes.size() == 0)
        {
            dd::aabb(currentNode->m_AABB->minPoint,
                currentNode->m_AABB->maxPoint, dd::colors::Red);
        }
        else if (currentNode->m_LowerNodes.size() == 0)
        {
            dd::aabb(currentNode->m_AABB->minPoint,
                currentNode->m_AABB->maxPoint, dd::colors::Green);
        }
        
        for (Node* newNode : currentNode->m_LowerNodes)
        {
            Q.push(newNode);
        }
    }
}