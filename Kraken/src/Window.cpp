#include "Window.h"
#include <iostream>

Window::Window(const WindowInfo& info)
    : m_Destroyed(false)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    

    m_Window = glfwCreateWindow(info.Width, info.Height, info.Title, NULL, NULL);
    if (!m_Window)
    {
        std::cerr << "Failed to create GLFW window!\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    if (info.VSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    glfwMakeContextCurrent(m_Window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << "\n";
        exit(EXIT_FAILURE);
    }
}

void Window::RenderEntities()
{
    if (m_Entities.empty())
        return;

    for (auto &entity: m_Entities)
    {
        entity.Render();
    }
}

void Window::BeginFrame() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::EndFrame() const
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void Window::Destroy()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();

    m_Destroyed = true;
}

Window::~Window()
{
    if (!m_Destroyed)
        Destroy();
}