#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "ModuleRender.h"
#include "Math/Quat.h"
#include "Application.h"
#include "Camera.h"
#include "Mesh.h"
#include "ModuleEditor.h"
#include "OBJ_Loader.h"
#include <iostream>

int ModuleRender::ms_width, ModuleRender::ms_height;
float ModuleRender::ms_AspectRatio;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNormal;\n"
    "uniform mat4 viewProj;\n"
    "uniform mat4 model;\n"
    "out vec3 Normal;\n"
    "out vec3 FragPos;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = viewProj * model * vec4(aPos, 1.0);\n"
    "   Normal = mat3(transpose(inverse(model))) * aNormal;\n"  
    "   FragPos = vec3(model * vec4(aPos, 1.0));\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 Normal;"
    "in vec3 FragPos;"
    "void main()\n"
    "{\n"
    "   vec3 norm = normalize(Normal);\n"
    "   vec3 lightDir = normalize(vec3(10.f, 10.f, 10.f) - FragPos);\n"
    "   float diff = max(dot(norm, lightDir), 0.0);\n"
    "   vec3 diffuse = diff * vec3(1.f, 1.f, 1.f);\n"
    "   vec3 result = (0.2f + diffuse) * vec3(0.f, 0.f, 1.f);\n"
    "   FragColor = vec4(result, 1.0);\n"
    "}\n\0";


bool ModuleRender::Init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FluidSolver", NULL, NULL);
    ms_width = SCR_WIDTH;
    ms_height = SCR_HEIGHT;
    ms_AspectRatio = ms_width / ms_height;
    
    if (m_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);

    auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
        ModuleRender::ms_width = width;
        ModuleRender::ms_height = height;
        ModuleRender::ms_AspectRatio = (float)ms_width / (float)ms_height;
    };
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);   

    glewInit();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_TEXTURE_2D);

	glClearDepth(1.0f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
    glViewport(0, 0, ms_width, ms_height);


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_Mesh = new Mesh(App);
    objl::Loader loader;
    if (loader.LoadFile("test.obj"))
    {
        for (auto v : loader.LoadedVertices)
        {
            m_Mesh->m_Vertices.push_back(math::float3(v.Position.X, v.Position.Y, v.Position.Z));
            m_Mesh->m_Normals.push_back(math::float3(v.Normal.X, v.Normal.Y, v.Normal.Z));
        }
        for (auto i : loader.LoadedIndices)
        {
            m_Mesh->m_Indices.push_back(i);
        }
        m_Mesh->BuildTrisInfo();
        m_Mesh->LoadToGPU();
    }
    else
    {
        return false;
    }
    return true;
}
bool ModuleRender::PreUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return true;
}
bool ModuleRender::Update()
{
    glUseProgram(shaderProgram);
    SetViewProjectionUniform(App->m_Editor->m_Camera->m_Frustum.ComputeViewProjMatrix());
    m_Mesh->Draw(shaderProgram);

    return true;
}

bool ModuleRender::PostUpdate()
{
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(m_window);
    return !glfwWindowShouldClose(m_window);
}

bool ModuleRender::Clean()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
    return true;
}

void ModuleRender::SetViewProjectionUniform(const math::float4x4& viewProj)
{
    const unsigned int viewProjLoc = glGetUniformLocation(shaderProgram, "viewProj");
    glUniformMatrix4fv(viewProjLoc, 1, GL_TRUE, viewProj.ptr());
}