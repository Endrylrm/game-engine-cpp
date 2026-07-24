#include "engine/systems/RenderSystem.hpp"
#include "engine/core/graphics/Texture.hpp"
#include "engine/entities/components/Transform2D.hpp"
#include "engine/api/AssetsAPI.hpp"
#include "engine/api/EventsAPI.hpp"

void RenderSystem::onInit()
{
    spriteAdded = EventsAPI::connect<ComponentAddedEvent<SpriteRenderer>>(
        [&](const ComponentAddedEvent<SpriteRenderer> &event)
        {
            entities.push_back(event.entity);
        });
    spriteRemoved = EventsAPI::connect<ComponentRemovedEvent<SpriteRenderer>>(
        [&](const ComponentRemovedEvent<SpriteRenderer> &event)
        {
            std::erase(entities, event.entity);
        });
}

void RenderSystem::onRender(Renderer &renderer)
{
    for (auto *entity : entities)
    {
        if (!entity->isVisibleInHierarchy())
            return;

        SpriteRenderer &sprite = *entity->getComponent<SpriteRenderer>();
        Transform2D &transform = *entity->getComponent<Transform2D>();

        renderer.drawTexture(
            AssetsAPI::get<Texture>(sprite.textureId),
            transform.position.x,
            transform.position.y);
    }
}
