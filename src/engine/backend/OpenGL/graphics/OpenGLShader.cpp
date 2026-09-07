#include "engine/backend/OpenGL/graphics/OpenGLShader.hpp"

#include <glad/gl.h>

#include <engine/core/log/Log.hpp>

OpenGLShader::~OpenGLShader()
{
    if (program)
        glDeleteProgram(program);
}

bool OpenGLShader::init(const std::string &vertexSrc, const std::string &fragmentSrc)
{
    GLuint vertexShader = compile(GL_VERTEX_SHADER, vertexSrc);

    if (!vertexShader)
        return false;

    GLuint fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentSrc);

    if (!fragmentShader)
    {
        glDeleteShader(vertexShader);
        return false;
    }

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint success{};
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        LOG_ERROR("Linking Shaders failed:\n{}", infoLog);
        glDeleteProgram(program);
        program = 0;
        return false;
    }

    return true;
}

void OpenGLShader::use() const
{
    glUseProgram(program);
}

GLuint OpenGLShader::get() const
{
    return program;
}

bool OpenGLShader::isValid() const
{
    return program != 0;
}

void OpenGLShader::setMat3(const std::string &name, const glm::mat3 &value)
{
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void OpenGLShader::setMat4(const std::string &name, const glm::mat4 &value)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void OpenGLShader::setVec2(const std::string &name, const glm::vec2 &value)
{
    glUniform2f(glGetUniformLocation(program, name.c_str()), value.x, value.y);
}

void OpenGLShader::setVec3(const std::string &name, const glm::vec3 &value)
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z);
}

void OpenGLShader::setVec4(const std::string &name, const glm::vec4 &value)
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z, value.w);
}

void OpenGLShader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), static_cast<int>(value));
}

void OpenGLShader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void OpenGLShader::setUInt(const std::string &name, unsigned int value)
{
    glUniform1ui(glGetUniformLocation(program, name.c_str()), value);
}

void OpenGLShader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

GLuint OpenGLShader::compile(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char *sourcePtr = source.c_str();

    glShaderSource(shader, 1, &sourcePtr, nullptr);

    glCompileShader(shader);

    GLint success{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG_ERROR("Shader compilation failed:\n{}", infoLog);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}
