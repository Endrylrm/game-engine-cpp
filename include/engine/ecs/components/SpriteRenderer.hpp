#pragma once
#include <engine/assets/AssetHandle.hpp>
#include <engine/core/graphics/Texture.hpp>

struct SpriteRenderer
{
    explicit SpriteRenderer(AssetHandle<Texture> texture) : textureId(texture) {}

    AssetHandle<Texture> textureId;
};
