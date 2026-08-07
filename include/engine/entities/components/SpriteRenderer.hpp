#pragma once
#include <string>

#include <engine/assets/AssetHandle.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/entities/components/Component.hpp>
#include <engine/entities/components/events/ComponentEvents.hpp>

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(AssetHandle<Texture> textureId) : textureId(textureId) {}
    ~SpriteRenderer() override = default;

    void onAwake() override;
    void onDestruction() override;

    AssetHandle<Texture> textureId;
};
