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

constexpr size_t getVertexTypeSize(VertexType type)
{
    switch (type)
    {
    case VertexType::Float:
        return sizeof(float);
    case VertexType::Int:
        return sizeof(int);
    case VertexType::UInt:
        return sizeof(uint32_t);
    }

    return 0;
}

struct VertexAttribute
{
    VertexType type;
    uint32_t count;
    size_t offset;
};

struct VertexLayout
{
    std::vector<VertexAttribute> attributes;

    size_t getStride() const
    {
        size_t stride = 0;

        for (const auto &attribute : attributes)
        {
            stride = std::max(
                stride, attribute.offset + getVertexTypeSize(attribute.type) * attribute.count
            );
        }

        return stride;
    }
};

enum class PrimitiveType : uint8_t
{
    Points,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,

    // Tessellation
    Patches
};

struct Mesh
{
    std::vector<std::byte> vertices;
    std::vector<uint32_t> indices;
    VertexLayout vertexLayout;
    PrimitiveType primitiveType;
};

template <typename T>
Mesh makeMesh(
    std::span<const T> vertices,
    std::span<const uint32_t> indices,
    VertexLayout layout,
    PrimitiveType type
)
{
    Mesh mesh;

    auto bytes = std::as_bytes(vertices);

    mesh.vertices.assign(bytes.begin(), bytes.end());
    mesh.indices.assign(indices.begin(), indices.end());
    mesh.vertexLayout = std::move(layout);
    mesh.primitiveType = std::move(type);

    return mesh;
}
