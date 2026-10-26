#pragma once
#include <glad/gl.h>

#include "engine/renderer/descriptions/Mesh.hpp"
#include "engine/renderer/resources/Mesh.hpp"

class OpenGLMesh final : public Mesh
{
public:
    ~OpenGLMesh() override;
    bool init(const MeshDescription &desc);
    bool is_valid() const override;

    void bind() const;
    void unbind() const;
    void draw() const;

private:
    GLenum convert_primitive_type(PrimitiveType type);

    GLuint vao{};
    GLuint vbo{};
    GLuint ebo{};

    GLsizei index_count = 0;
    GLenum primitive_type;
};
