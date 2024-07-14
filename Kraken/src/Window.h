#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Entity.h"

struct WindowInfo
{
    const char* Title;
    uint32_t Width, Height;
    bool VSync;
};

class Window
{
public:
    Window(const WindowInfo& info);
    ~Window();

    void Destroy();

    void RegisterEntity(Entity& entity) { m_Entities.push_back(entity); }
    void RenderEntities();
    const std::vector<Entity>& GetEntities() const { return m_Entities; }
    std::vector<Entity>& GetEntities() { return m_Entities; }

    GLFWwindow* GetGLFWWindow() const { return m_Window; }

    void BeginFrame() const;
    void EndFrame() const;

    bool IsRunning() const { return !glfwWindowShouldClose(m_Window); };

private:
    std::vector<Entity> m_Entities;

    GLFWwindow* m_Window;
    bool m_Destroyed;
};