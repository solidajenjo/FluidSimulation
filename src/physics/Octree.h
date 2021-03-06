#pragma once
#include <vector>
#include <Geometry/AABB.h>

struct TriangleData;
class Mesh;

typedef unsigned uint;

struct Node
{
    Node();
    Node(const math::float3& pos, const math::float3& size, uint depth);
	~Node();

	void Flush();

	unsigned m_Depth = 0u;
	math::AABB* m_AABB { nullptr };
	std::vector<const TriangleData*> m_Bucket;
	std::vector<Node*> m_LowerNodes;
};

class Octree
{
public:

    ~Octree();

    Node* m_Root { nullptr };

    void Calculate(const math::AABB& rootAABB, const std::vector<Mesh*>& meshes, uint maxDepth);
	std::vector<const TriangleData*> GetPossibleCollisions(const math::AABB* aabb) const;
	void DebugDraw();
};