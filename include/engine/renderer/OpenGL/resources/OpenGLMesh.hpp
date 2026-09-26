#pragma once
#include <glad/gl.h>

#include <engine/renderer/descriptions/Mesh.hpp>
#include <engine/renderer/resources/Mesh.hpp>

class OpenGLMesh
{
public:
    ~OpenGLMesh();
    bool init(const MeshDescription &desc);
    bool isValid() const;

    void bind() const;
    void unbind() const;
    void draw() const;

private:
    GLenum convertPrimitiveType(PrimitiveType type);

    GLuint vao{};
    GLuint vbo{};
    GLuint ebo{};

    GLsizei indexCount = 0;
    GLenum primitiveType;
};
