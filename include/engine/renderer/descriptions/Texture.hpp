#pragma once
#include <cstdint>

enum class TextureFormat
{
    R8Unorm,
    RG8Unorm,
    RgB8Unorm,
    RgbA8Unorm,

    R16Unorm,
    RG16Unorm,
    RgB16Unorm,
    RgbA16Unorm,

    R16Float,
    RG16Float,
    RgB16Float,
    RgbA16Float,

    R32Float,
    RG32Float,
    RgB32Float,
    RgbA32Float,

    Depth24Stencil8,
    Depth32Float,
};

enum class TextureDimension
{
    Texture2D,
    Texture3D,
    Cube,
};

enum class TextureUsage : uint32_t
{
    None = 0,
    Sampled = 1 << 0,
    RenderTarget = 1 << 1,
    DepthStencil = 1 << 2,
    Storage = 1 << 3,
    TransferSource = 1 << 4,
    TransferDest = 1 << 5,
};

struct TextureData
{
    const void *data = nullptr;
    size_t size = 0;
    uint32_t row_pitch = 0;
};

struct TextureDescription
{
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;
    uint32_t mip_levels = 1;

    TextureFormat format = TextureFormat::RgbA8Unorm;
    TextureDimension dimension = TextureDimension::Texture2D;
    TextureUsage usage = TextureUsage::Sampled;

    TextureData data{};
};
