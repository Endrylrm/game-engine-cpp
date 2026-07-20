#pragma once
#include <string>
#include "engine/entities/components/Component.hpp"
#include "engine/assets/AssetHandle.hpp"
#include "engine/core/graphics/Texture.hpp"

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(AssetHandle<Texture> textureId) : textureId(textureId) {}
    ~SpriteRenderer() override = default;

    AssetHandle<Texture> textureId;
};
