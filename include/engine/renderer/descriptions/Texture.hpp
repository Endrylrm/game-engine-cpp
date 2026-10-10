#pragma once
#include <cstdint>

enum class TextureFormat
{
    R8_UNORM,
    RG8_UNORM,
    RGB8_UNORM,
    RGBA8_UNORM,

    R16_UNORM,
    RG16_UNORM,
    RGB16_UNORM,
    RGBA16_UNORM,

    R16_FLOAT,
    RG16_FLOAT,
    RGB16_FLOAT,
    RGBA16_FLOAT,

    R32_FLOAT,
    RG32_FLOAT,
    RGB32_FLOAT,
    RGBA32_FLOAT,

    Depth24Stencil8,
    Depth32_FLOAT,
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
    uint32_t rowPitch = 0;
};

struct TextureDescription
{
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;
    uint32_t mipLevels = 1;

    TextureFormat format = TextureFormat::RGBA8_UNORM;
    TextureDimension dimension = TextureDimension::Texture2D;
    TextureUsage usage = TextureUsage::Sampled;

    TextureData data{};
};
