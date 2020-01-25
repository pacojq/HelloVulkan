#include "Application.h"


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>


void Application::Init()
{
    int success = glfwInit();
    ASSERT(success, "Could not initialize GLFW!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_Window = glfwCreateWindow(800, 600, "Hello Vulkan", nullptr, nullptr);

    m_Renderer = std::make_unique<VulkanRenderer>(m_Window);
    m_Renderer->Init();
}


void Application::MainLoop()
{
    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();
    }
}


void Application::CleanUp()
{
    m_Renderer->CleanUp();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}