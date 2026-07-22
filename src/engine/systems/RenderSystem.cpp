#include "engine/systems/RenderSystem.hpp"
#include "engine/core/graphics/Texture.hpp"
#include "engine/entities/components/SpriteRenderer.hpp"
#include "engine/entities/components/Transform2D.hpp"
#include "engine/api/AssetsAPI.hpp"

void RenderSystem::render(EntityManager &entityManager, Renderer &renderer)
{
    entityManager.forEach<SpriteRenderer, Transform2D>(
        [&](Entity &entity, SpriteRenderer &sprite, Transform2D &transform)
        {
            if (!entity.isVisibleInHierarchy())
                return;

            renderer.drawTexture(
                AssetsAPI::get<Texture>(sprite.textureId),
                transform.position.x,
                transform.position.y);
        });
}
