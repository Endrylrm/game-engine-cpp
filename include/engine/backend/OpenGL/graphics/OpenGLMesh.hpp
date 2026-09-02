#pragma once
#include <glad/gl.h>

#include <engine/core/graphics/Mesh.hpp>
#include <engine/core/graphics/MeshData.hpp>

class OpenGLMesh : public Mesh
{
public:
    ~OpenGLMesh() override;
    bool init(const MeshData &data) override;
    bool isValid() const override;

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
