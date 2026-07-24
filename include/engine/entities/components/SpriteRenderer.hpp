#pragma once
#include <string>
#include "engine/entities/components/Component.hpp"
#include "engine/assets/AssetHandle.hpp"
#include "engine/core/graphics/Texture.hpp"
#include "engine/api/EventsAPI.hpp"
#include "engine/entities/components/events/ComponentEvents.hpp"

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(AssetHandle<Texture> textureId) : textureId(textureId) {}
    ~SpriteRenderer() override = default;

    void onAwake() override
    {
        EventsAPI::emit(ComponentAddedEvent<SpriteRenderer>{owner, this});
    }

    void onDestruction() override
    {
        EventsAPI::emit(ComponentRemovedEvent<SpriteRenderer>{owner, this});
    }

    AssetHandle<Texture> textureId;
};
