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
        return sizeof(int32_t);
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

    constexpr size_t getSize() const
    {
        return getVertexTypeSize(type) * count;
    }
};

struct VertexLayout
{
    std::vector<VertexAttribute> attributes;

    size_t getStride() const
    {
        size_t stride = 0;

        for (const auto &attribute : attributes)
        {
            stride = std::max(stride, attribute.offset + attribute.getSize());
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

struct MeshDescription
{
    std::vector<std::byte> vertices;
    std::vector<uint32_t> indices;
    VertexLayout vertexLayout;
    PrimitiveType primitiveType;
};

template <typename T>
MeshDescription makeMeshDescription(
    std::span<const T> vertices,
    std::span<const uint32_t> indices,
    VertexLayout layout,
    PrimitiveType type
)
{
    MeshDescription desc;

    auto bytes = std::as_bytes(vertices);

    desc.vertices.assign(bytes.begin(), bytes.end());
    desc.indices.assign(indices.begin(), indices.end());
    desc.vertexLayout = std::move(layout);
    desc.primitiveType = type;

    return desc;
}
