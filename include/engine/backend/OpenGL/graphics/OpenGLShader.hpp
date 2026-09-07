#pragma once
#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>

class OpenGLShader
{
public:
    OpenGLShader() = default;
    ~OpenGLShader();

    bool init(const std::string &vertexSrc, const std::string &fragmentSrc);

    void use() const;

    GLuint get() const;
    bool isValid() const;

    void setMat3(const std::string &name, const glm::mat3 &value);
    void setMat4(const std::string &name, const glm::mat4 &value);
    void setVec2(const std::string &name, const glm::vec2 &value);
    void setVec3(const std::string &name, const glm::vec3 &value);
    void setVec4(const std::string &name, const glm::vec4 &value);
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setUInt(const std::string &name, unsigned int value);
    void setFloat(const std::string &name, float value);

private:
    GLuint compile(GLenum type, const std::string &source);

    GLuint program{};
};
