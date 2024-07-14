//
// Created by root on 07/07/24.
//

#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace Kraken
{
    class Shader
    {
    public:
        Shader(const char *shaderPath);

        ~Shader();

        const uint32_t GetId() const
        { return m_Id; }

        void SetUniformMat4f(const char *name, const glm::mat4 &matrix);

        void Bind() const;

        void Unbind() const;

    private:
        uint32_t Compile(uint32_t type, const char *src);

        void Parse(const char *shaderPath);

        void Create();

    private:
        uint32_t m_Id;

        struct ShaderProgramSource
        {
            std::string VertexSource;
            std::string FragmentSource;
        } m_Src;
    };
}