#include <Game.h>
#include <Shader.h>
#include <Entity.h>
#include <Window.h>

class Test final : public Kraken::Game
{
public:
    Test() : Game(), m_Window({"Best Game Ever", 800, 600})
    {
    }

    void Run() override
    {
        const std::vector vertices =
        {
            Kraken::Vertex({-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}),
            Kraken::Vertex({0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}),
            Kraken::Vertex({0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}),
            Kraken::Vertex({-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f})
        };

        const std::vector<uint32_t> indices =
        {
            0, 1, 2,
            2, 3, 0
        };

        const Kraken::Shader shader("../res/test.Shader");
        Kraken::Entity e(vertices, indices, shader);
        m_Window.RegisterEntity(e);

        while (m_Window.IsRunning())
        {
            m_Window.BeginFrame();
            m_Window.RenderEntities();
            m_Window.EndFrame();
        }

        Stop();
    }

    void Stop() override
    {
        m_Window.Destroy();
    }
private:
    Kraken::Window m_Window;
};

int main()
{
    Test test;
    test.Run();
}