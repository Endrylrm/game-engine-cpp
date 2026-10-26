#include "engine/renderer/OpenGL/resources/OpenGLShader.hpp"

#include <vector>

#include <glad/gl.h>

#include "engine/core/log/Log.hpp"

OpenGLShader::~OpenGLShader()
{
    if (program)
        glDeleteProgram(program);
}

bool OpenGLShader::init(const ShaderDescription &desc)
{
    if (desc.sources.empty())
    {
        LOG_ERROR("Shader description contains no shader sources");
        return false;
    }

    std::vector<GLuint> shaders;
    shaders.reserve(desc.sources.size());

    for (const auto &shaderSource : desc.sources)
    {
        const GLuint shader =
            compile(convert_shader_stage(shaderSource.stage), shaderSource.source);

        if (!shader)
        {
            for (const GLuint compiledShader : shaders)
                glDeleteShader(compiledShader);

            return false;
        }

        shaders.push_back(shader);
    }

    program = glCreateProgram();

    for (const GLuint shader : shaders)
        glAttachShader(program, shader);

    glLinkProgram(program);

    GLint success{};
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    for (const GLuint shader : shaders)
        glDeleteShader(shader);

    if (!success)
    {
        GLchar info_log[512];
        glGetProgramInfoLog(program, 512, NULL, info_log);
        LOG_ERROR("Linking Shaders failed:\n{}", info_log);
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

bool OpenGLShader::is_valid() const
{
    return program != 0;
}

void OpenGLShader::set(const std::string &name, const glm::mat3 &value) const
{
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void OpenGLShader::set(const std::string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void OpenGLShader::set(const std::string &name, const glm::vec2 &value) const
{
    glUniform2f(glGetUniformLocation(program, name.c_str()), value.x, value.y);
}

void OpenGLShader::set(const std::string &name, const glm::vec3 &value) const
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z);
}

void OpenGLShader::set(const std::string &name, const glm::vec4 &value) const
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z, value.w);
}

void OpenGLShader::set(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), static_cast<int>(value));
}

void OpenGLShader::set(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void OpenGLShader::set(const std::string &name, unsigned int value) const
{
    glUniform1ui(glGetUniformLocation(program, name.c_str()), value);
}

void OpenGLShader::set(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

GLuint OpenGLShader::compile(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char *source_ptr = source.c_str();

    glShaderSource(shader, 1, &source_ptr, nullptr);

    glCompileShader(shader);

    GLint success{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        LOG_ERROR("Shader compilation failed:\n{}", info_log);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLenum OpenGLShader::convert_shader_stage(ShaderStage stage)
{
    switch (stage)
    {
    case ShaderStage::Vertex:
        return GL_VERTEX_SHADER;
    case ShaderStage::Fragment:
        return GL_FRAGMENT_SHADER;
    case ShaderStage::Geometry:
        return GL_GEOMETRY_SHADER;
    case ShaderStage::Compute:
        return GL_COMPUTE_SHADER;
    case ShaderStage::TessellationControl:
        return GL_TESS_CONTROL_SHADER;
    case ShaderStage::TessellationEvaluation:
        return GL_TESS_EVALUATION_SHADER;
    }

    LOG_ERROR("Invalid shader stage");
    return 0;
}
