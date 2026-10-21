#pragma once
#include "engine/assets/AssetHandle.hpp"
#include "engine/renderer/resources/Texture.hpp"

struct Sprite
{
    explicit Sprite(AssetHandle<Texture> texture) : textureId(texture) {}

    AssetHandle<Texture> textureId;
};
