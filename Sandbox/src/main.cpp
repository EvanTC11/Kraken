#include <Game.h>
#include <Shader.h>
#include <Entity.h>
#include <Window.h>
#include <OrthographicCamera.h>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 800
#define HEIGHT 600

class Test final : public Kraken::Game
{
public:
    Test() : Game(), m_Window({"Best Game Ever", WIDTH, HEIGHT}), m_Camera(0.0f, (float)WIDTH, 0.0f, float(HEIGHT))
    {
    }

    void Run() override
    {
        const std::vector vertices =
        {
            Kraken::Vertex({(float)WIDTH / 2.0f - 50.0f, (float)HEIGHT / 2.0f - 50.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}),
            Kraken::Vertex({(float)WIDTH / 2.0f + 50.0f, (float)HEIGHT / 2.0f - 50.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}),
            Kraken::Vertex({(float)WIDTH / 2.0f + 50.0f, (float)HEIGHT / 2.0f + 50.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}),
            Kraken::Vertex({(float)WIDTH / 2.0f - 50.0f, (float)HEIGHT / 2.0f + 50.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f})
        };

        const std::vector<uint32_t> indices =
        {
            0, 1, 2,
            2, 3, 0
        };

        const Kraken::Shader shader("../res/test.Shader");
        Kraken::Entity e(vertices, indices, shader);
        m_Window.RegisterEntity(e);

        const static GLint location = glGetUniformLocation(shader.GetId(), "u_ViewProjectionMatrix");
        if (location == -1)
        {
            std::cerr << "Uniform 'u_ViewProjectionMatrix' not found in shader" << std::endl;
            Stop();
            return;
        }

        while (m_Window.IsRunning())
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            shader.Bind();
            e.Bind();
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_Camera.GetViewProjectionMatrix()));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(m_Window.GetGLFWWindow());
            glfwPollEvents();
        }

        Stop();
    }

    void Stop() override
    {
        m_Window.Destroy();
    }
private:
    Kraken::Window m_Window;
    Kraken::OrthographicCamera m_Camera;
};

int main()
{
    Test test;
    test.Run();
}