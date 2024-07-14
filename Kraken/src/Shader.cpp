//
// Created by root on 07/07/24.
//

#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>

Shader::Shader(const char* shaderPath)
{
    Parse(shaderPath);
    Create();
}

Shader::~Shader()
{
    Unbind();
    glDeleteProgram(m_Id);
}

void Shader::SetUniformMat4f(const char* name, const glm::mat4& matrix)
{
    static int location = glGetUniformLocation(m_Id, name);
    if (!location)
    {
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::Bind() const
{
    glUseProgram(m_Id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

uint32_t Shader::Compile(uint32_t type, const char* src)
{
    uint32_t id = glCreateShader(type);

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);
    if (res == false)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        char* message = (char*)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);

        glDeleteShader(id);
        return 0;
    }

    return id;
}

void Shader::Parse(const char* shaderPath)
{
    std::ifstream stream(shaderPath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }

            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }

        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    m_Src = { ss[0].str(), ss[1].str() };
}

void Shader::Create()
{
    m_Id = glCreateProgram();

    uint32_t vs = Compile(GL_VERTEX_SHADER, m_Src.VertexSource.c_str());
    uint32_t fs = Compile(GL_FRAGMENT_SHADER, m_Src.FragmentSource.c_str());

    glAttachShader(m_Id, vs);
    glAttachShader(m_Id, fs);

    glLinkProgram(m_Id);
    glValidateProgram(m_Id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}