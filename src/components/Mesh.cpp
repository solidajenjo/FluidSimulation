#include "Mesh.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Transform.h"

Mesh::Mesh(Application* App) : Component(App)
{
    m_Transform = new Transform(App);
}

Mesh::~Mesh()
{
    delete m_Transform;
}

void Mesh::Draw(int shaderProgram)
{
    const unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, m_Transform->m_Global.ptr());
    glBindVertexArray(m_VAO); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VIO);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::LoadToGPU()
{
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &m_VIO);

    glBindVertexArray(VAO);
    m_VAO = VAO;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * m_Vertices.size() * sizeof(math::float3), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(math::float3), &m_Vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(math::float3), m_Normals.size() * sizeof(math::float3), &m_Normals[0]);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::float3), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(math::float3), (void*)(m_Vertices.size() * sizeof(math::float3)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VIO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * m_Indices.size(), &m_Indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 


}

void Mesh::BuildTrisInfo()
{
    assert(m_Indices.size() % 3 == 0);

    for (size_t i = 0; i < m_Indices.size(); i += 3)
    {
        math::Triangle tri;
        tri.a = m_Vertices[m_Indices[i]];
        tri.b = m_Vertices[m_Indices[i + 1]];
        tri.c = m_Vertices[m_Indices[i + 2]];
        m_Triangles.push_back(tri);
    }
}