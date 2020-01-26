#include "Application.h"


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>


void Application::Init()
{
    uint32_t width = 800;
    uint32_t height = 600;

    int success = glfwInit();
    ASSERT(success, "Could not initialize GLFW!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_Window = glfwCreateWindow(width, height, "Hello Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(m_Window, this);
    
    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        app->m_Renderer->OnWindowResize(width, height);
    });

    m_Renderer = std::make_unique<VulkanRenderer>(m_Window);
    m_Renderer->Init();
}


void Application::MainLoop()
{
    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while (!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();
        m_Renderer->DrawFrame();
    }

    m_Renderer->ExitMainLoop();
}





void Application::CleanUp()
{
    m_Renderer->CleanUp();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}