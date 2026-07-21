#include "engine/systems/RenderSystem.hpp"
#include "engine/core/graphics/Texture.hpp"
#include "engine/entities/components/SpriteRenderer.hpp"
#include "engine/entities/components/Transform2D.hpp"
#include "engine/api/AssetsAPI.hpp"

void RenderSystem::render(EntityManager &entityManager, Renderer &renderer)
{
    entityManager.forEachComponent<SpriteRenderer, Transform2D>(
        [&](SpriteRenderer *sprite, Transform2D *transform)
        {
            renderer.drawTexture(
                AssetsAPI::get<Texture>(sprite->textureId),
                transform->position.x,
                transform->position.y);
        });
}
