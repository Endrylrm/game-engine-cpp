#pragma once
#include <cstdint>
#include <span>
#include <vector>

enum class VertexType
{
    Float,
    Int,
    UInt
};

struct VertexAttribute
{
    VertexType type;
    uint32_t location;
    uint32_t count;
    size_t offset;
};

struct VertexLayout
{
    std::vector<VertexAttribute> attributes;
    uint32_t stride;
};

enum class PrimitiveType
{
    Points,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,

    // Tessellation
    Patches
};

struct MeshData
{
    std::vector<std::byte> vertices;
    std::vector<uint32_t> indices;
    VertexLayout vertexLayout;
    PrimitiveType primitiveType;

    size_t vertexCount() const
    {
        return vertices.size() / vertexLayout.stride;
    }

    size_t indexCount() const
    {
        return indices.size();
    }
};

template <typename T>
MeshData makeMeshData(
    std::span<const T> vertices,
    std::span<const uint32_t> indices,
    VertexLayout layout,
    PrimitiveType type
)
{
    MeshData mesh;

    auto bytes = std::as_bytes(vertices);

    mesh.vertices.assign(bytes.begin(), bytes.end());
    mesh.indices.assign(indices.begin(), indices.end());
    mesh.vertexLayout = std::move(layout);
    mesh.primitiveType = std::move(type);

    return mesh;
}
