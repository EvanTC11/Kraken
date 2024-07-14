#include "Entity.h"

#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace Kraken
{
    Entity::Entity(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, const Shader &shader)
            : m_Vertices(vertices), m_Indices(indices), m_Vao(0), m_Vbo(0), m_Ibo(0), m_Shader(shader)
    {
        m_IndexCount = m_Indices.size();
        BufferData();
    }

    Entity::Entity(const char *path, const Shader &shader) : m_Vao(0), m_Vbo(0), m_Ibo(0), m_Shader(shader)
    {
        Assimp::Importer importer;
        Assimp::DefaultLogger::create("ENTITY DEBUGGER", Assimp::Logger::VERBOSE, aiDefaultLogStream_STDOUT);

        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "Failed to load model: " << importer.GetErrorString() << std::endl;
            return;
        }

        m_IndexCount = scene->mMeshes[0]->mNumFaces * 3;

        ProcessNode(scene, scene->mRootNode);
        Assimp::DefaultLogger::kill();

        BufferData();
    }

    Entity::~Entity()
    {
        glDeleteVertexArrays(1, &m_Vao);
        glDeleteBuffers(1, &m_Vbo);
        glDeleteBuffers(1, &m_Ibo);
    }

    void Entity::Bind() const
    {
        glBindVertexArray(m_Vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
    }

    void Entity::Unbind()
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Entity::ProcessMesh(const aiMesh *mesh)
    {
        for (uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            glm::vec3 position = {};
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;

            glm::vec3 normal = {};
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;

            glm::vec2 uv(0.0f, 0.0f);
            if (mesh->mTextureCoords[0])
            {
                uv.x = mesh->mTextureCoords[0][i].x;
                uv.y = mesh->mTextureCoords[0][i].y;
            }

            m_Vertices.emplace_back(position, normal, uv);
        }

        for (uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace face = mesh->mFaces[i];
            for (size_t j = 0; j < face.mNumIndices; j++)
            {
                m_Indices.push_back(face.mIndices[j]);
            }
        }
    }

    void Entity::ProcessNode(const aiScene *scene, aiNode *node)
    {
        for (uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(mesh);
        }

        for (uint32_t i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(scene, node->mChildren[i]);
        }

    }

    void Entity::Render()
    {
        m_Shader.Bind();
        Bind();
        glDrawElements(GL_TRIANGLES, (int) m_IndexCount, GL_UNSIGNED_INT, nullptr);
    }

    void Entity::BufferData()
    {
        glGenVertexArrays(1, &m_Vao);
        glBindVertexArray(m_Vao);

        glGenBuffers(1, &m_Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

        // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Position));

        // Normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));

        // UV
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Uv));

        glGenBuffers(1, &m_Ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(uint32_t), m_Indices.data(), GL_STATIC_DRAW);
    }
}