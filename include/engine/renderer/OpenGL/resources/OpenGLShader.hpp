#pragma once
#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <engine/renderer/descriptions/Shader.hpp>

class OpenGLShader
{
public:
    OpenGLShader() = default;
    ~OpenGLShader();

    bool init(const ShaderDescription &desc);

    void use() const;

    GLuint get() const;
    bool isValid() const;

    void set(const std::string &name, const glm::mat3 &value) const;
    void set(const std::string &name, const glm::mat4 &value) const;
    void set(const std::string &name, const glm::vec2 &value) const;
    void set(const std::string &name, const glm::vec3 &value) const;
    void set(const std::string &name, const glm::vec4 &value) const;
    void set(const std::string &name, bool value) const;
    void set(const std::string &name, int value) const;
    void set(const std::string &name, unsigned int value) const;
    void set(const std::string &name, float value) const;

private:
    GLuint compile(GLenum type, const std::string &source);
    GLenum convertShaderStage(ShaderStage stage);

    GLuint program{};
};
