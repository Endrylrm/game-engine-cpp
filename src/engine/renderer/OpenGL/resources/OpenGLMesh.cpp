#include "engine/renderer/OpenGL/resources/OpenGLMesh.hpp"

#include "engine/core/log/Log.hpp"

OpenGLMesh::~OpenGLMesh()
{
    if (ebo)
        glDeleteBuffers(1, &ebo);

    if (vbo)
        glDeleteBuffers(1, &vbo);

    if (vao)
        glDeleteVertexArrays(1, &vao);
}

bool OpenGLMesh::init(const MeshDescription &desc)
{
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    if (!vbo || !vao || !ebo)
    {
        LOG_ERROR("Failed to create OpenGL texture buffers.");
        return false;
    }

    index_count = static_cast<GLsizei>(desc.indices.size());
    primitive_type = convert_primitive_type(desc.primitive_type);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, desc.vertices.size(), desc.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        desc.indices.size() * sizeof(uint32_t),
        desc.indices.data(),
        GL_STATIC_DRAW
    );

    size_t stride = desc.vertex_layout.get_stride();

    GLuint location = 0;

    for (VertexAttribute attrib : desc.vertex_layout.attributes)
    {
        switch (attrib.type)
        {
        case VertexType::Float:
            glVertexAttribPointer(
                location,
                attrib.count,
                GL_FLOAT,
                GL_FALSE,
                stride,
                reinterpret_cast<void *>(attrib.offset)
            );
            break;
        case VertexType::Int:
            glVertexAttribIPointer(
                location, attrib.count, GL_INT, stride, reinterpret_cast<void *>(attrib.offset)
            );
            break;
        case VertexType::UInt:
            glVertexAttribIPointer(
                location,
                attrib.count,
                GL_UNSIGNED_INT,
                stride,
                reinterpret_cast<void *>(attrib.offset)
            );
            break;
        default:
            LOG_ERROR("Unsupported vertex attribute type.");
            return false;
        }

        glEnableVertexAttribArray(location);
        ++location;
    }

    glBindVertexArray(0);
    return true;
}

bool OpenGLMesh::is_valid() const
{
    return vbo != 0 && vao != 0 && ebo != 0;
}

void OpenGLMesh::bind() const
{
    glBindVertexArray(vao);
}

void OpenGLMesh::unbind() const
{
    glBindVertexArray(0);
}

void OpenGLMesh::draw() const
{
    bind();
    glDrawElements(primitive_type, index_count, GL_UNSIGNED_INT, nullptr);
}

GLenum OpenGLMesh::convert_primitive_type(PrimitiveType type)
{
    switch (type)
    {
    case PrimitiveType::Points:
        return GL_POINTS;
    case PrimitiveType::Triangles:
        return GL_TRIANGLES;
    case PrimitiveType::TriangleStrip:
        return GL_TRIANGLE_STRIP;
    case PrimitiveType::Lines:
        return GL_LINES;
    case PrimitiveType::LineStrip:
        return GL_LINE_STRIP;
    case PrimitiveType::Patches:
        return GL_PATCHES;
    }

    return GL_TRIANGLES;
}
