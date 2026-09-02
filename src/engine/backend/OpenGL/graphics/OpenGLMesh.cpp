#include "engine/backend/OpenGL/graphics/OpenGLMesh.hpp"

#include <engine/core/log/Log.hpp>

OpenGLMesh::~OpenGLMesh()
{
    if (ebo)
        glDeleteBuffers(1, &ebo);

    if (vbo)
        glDeleteBuffers(1, &vbo);

    if (vao)
        glDeleteVertexArrays(1, &vao);
}

bool OpenGLMesh::init(const MeshData &data)
{
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    if (!vbo || !vao || !ebo)
    {
        LOG_ERROR("Failed to create OpenGL texture buffers.");
        return false;
    }

    indexCount = static_cast<GLsizei>(data.indexCount());
    primitiveType = convertPrimitiveType(data.primitiveType);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.vertices.size(), data.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        data.indices.size() * sizeof(uint32_t),
        data.indices.data(),
        GL_STATIC_DRAW
    );

    for (VertexAttribute attrib : data.vertexLayout.attributes)
    {
        switch (attrib.type)
        {
        case VertexType::Float:
            glVertexAttribPointer(
                attrib.location,
                attrib.count,
                GL_FLOAT,
                GL_FALSE,
                data.vertexLayout.stride,
                reinterpret_cast<void *>(attrib.offset)
            );
            glEnableVertexAttribArray(attrib.location);
            break;
        case VertexType::Int:
            glVertexAttribIPointer(
                attrib.location,
                attrib.count,
                GL_INT,
                data.vertexLayout.stride,
                reinterpret_cast<void *>(attrib.offset)
            );
            glEnableVertexAttribArray(attrib.location);
            break;
        case VertexType::UInt:
            glVertexAttribIPointer(
                attrib.location,
                attrib.count,
                GL_UNSIGNED_INT,
                data.vertexLayout.stride,
                reinterpret_cast<void *>(attrib.offset)
            );
            glEnableVertexAttribArray(attrib.location);
            break;
        default:
            LOG_ERROR("Unsupported vertex attribute type.");
            return false;
        }
    }

    glBindVertexArray(0);
    return true;
}

bool OpenGLMesh::isValid() const
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
    glDrawElements(primitiveType, indexCount, GL_UNSIGNED_INT, nullptr);
}

GLenum OpenGLMesh::convertPrimitiveType(PrimitiveType type)
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
