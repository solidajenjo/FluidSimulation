#pragma once
#include <Component.h>
#include <vector>
#include "Math/float3.h"
#include "Geometry/Triangle.h"

class Transform;

struct TriangleData
{
    TriangleData(const math::Triangle& triangle, const math::float3& normal) : 
        m_Triangle(triangle) , m_Normal(normal) {}
    math::Triangle m_Triangle;
    math::float3 m_Normal;
};

typedef std::vector<math::float3> t_F3Vec;
typedef std::vector<uint> t_UintVec;
typedef std::vector<TriangleData> t_TrisVec;

class Mesh : public Component
{
public:

    Mesh(Application* App);

    virtual ~Mesh();

    void Draw(int shaderProgram);
    void Update() override {};
    void LoadToGPU();
    void BuildTrisInfo();

    t_F3Vec m_Vertices;
    t_F3Vec m_Normals;
    t_UintVec m_Indices;
    t_TrisVec m_Triangles;

    uint m_VAO = 0, m_VIO = 0;
    Transform* m_Transform { nullptr };

};