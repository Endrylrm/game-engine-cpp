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

constexpr size_t get_vertex_type_size(VertexType type)
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

    constexpr size_t get_size() const
    {
        return get_vertex_type_size(type) * count;
    }
};

struct VertexLayout
{
    std::vector<VertexAttribute> attributes;

    size_t get_stride() const
    {
        size_t stride = 0;

        for (const auto &attribute : attributes)
        {
            stride = std::max(stride, attribute.offset + attribute.get_size());
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
    VertexLayout vertex_layout;
    PrimitiveType primitive_type;
};

template <typename T>
MeshDescription make_mesh_description(
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
    desc.vertex_layout = std::move(layout);
    desc.primitive_type = type;

    return desc;
}
