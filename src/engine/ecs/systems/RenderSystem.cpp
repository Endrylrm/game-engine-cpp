#include "engine/ecs/systems/RenderSystem.hpp"

#include <engine/api/AssetsAPI.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/ecs/components/Renderable.hpp>
#include <engine/ecs/components/SpriteRenderer.hpp>
#include <engine/ecs/components/Transform.hpp>

void RenderSystem::onRender(World &world, Renderer &renderer)
{
    for (auto [sprite, transform, _] : world.view<SpriteRenderer, Transform, Renderable>())
    {
        auto *texture = AssetsAPI::get<Texture>(sprite.textureId);
        auto position = transform.position;

        renderer.drawTexture(texture, position.x, position.y);
    }
}
