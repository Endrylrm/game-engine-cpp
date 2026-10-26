#pragma once

enum class TextureFilter
{
    Nearest,
    Linear,
};

enum class TextureWrap
{
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder,
};

struct SamplerDescription
{
    TextureFilter min_filter = TextureFilter::Linear;
    TextureFilter mag_filter = TextureFilter::Linear;

    TextureWrap wrapU = TextureWrap::ClampToEdge;
    TextureWrap wrapV = TextureWrap::ClampToEdge;
    TextureWrap wrapW = TextureWrap::ClampToEdge;
};
