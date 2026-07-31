#include "engine/systems/RenderSystem.hpp"

#include "engine/api/AssetsAPI.hpp"
#include "engine/api/EventsAPI.hpp"
#include "engine/core/graphics/Texture.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/entities/components/Transform.hpp"

void RenderSystem::onInit()
{
    spriteAdded = eventBus->connect<ComponentAddedEvent<SpriteRenderer>>(
        [&](const ComponentAddedEvent<SpriteRenderer> &event)
        { sprites.push_back(event.component); }
    );
    spriteRemoved = eventBus->connect<ComponentRemovedEvent<SpriteRenderer>>(
        [&](const ComponentRemovedEvent<SpriteRenderer> &event)
        { std::erase(sprites, event.component); }
    );
}

void RenderSystem::onUnload()
{
    spriteAdded.disconnect();
    spriteRemoved.disconnect();
    sprites.clear();
}

void RenderSystem::onRender(Renderer &renderer)
{
    for (auto *sprite : sprites)
    {
        Entity &entity = *sprite->owner;

        if (!entity.isVisibleInHierarchy())
            continue;

        Transform &transform = *entity.getComponent<Transform>();

        auto texture = AssetsAPI::get<Texture>(sprite->textureId);
        auto position = transform.position;

        renderer.drawTexture(texture, position.x, transform.position.y);
    }
}
