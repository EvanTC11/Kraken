#pragma once

#include "Shader.h"

#include <assimp/mesh.h>
#include <assimp/scene.h>

#include <glm/glm.hpp>
#include <vector>

namespace Kraken
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 Uv;

        Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &uv) : Position(position),
                                                                                          Normal(normal), Uv(uv)
        {}
    };

    class Entity
    {
    public:
        Entity(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, const Shader &shader);

        Entity(const char *path, const Shader &shader);

        ~Entity();

        void Bind() const;

        static void Unbind();

        void SetShader(const Shader &shader)
        { m_Shader = shader; }

        const Shader &GetShader() const
        { return m_Shader; }

        virtual void Render();

    private:
        void ProcessMesh(const aiMesh *mesh);

        void ProcessNode(const aiScene *scene, aiNode *node);

        void BufferData();

    private:
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;

        uint32_t m_Vao, m_Vbo, m_Ibo;
        size_t m_IndexCount;

        Shader m_Shader;
    };
}