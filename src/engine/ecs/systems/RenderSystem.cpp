#include "engine/ecs/systems/RenderSystem.hpp"

#include <engine/api/AssetsAPI.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/ecs/components/SpriteRenderer.hpp>
#include <engine/ecs/components/Transform.hpp>
#include <engine/ecs/components/Visible.hpp>

void RenderSystem::onRender(Renderer &renderer)
{
    for (auto [sprite, transform, v] : registry.view<SpriteRenderer, Transform, Visible>())
    {
        auto *texture = AssetsAPI::get<Texture>(sprite.textureId);
        auto position = transform.position;

        renderer.drawTexture(texture, position.x, position.y);
    }
}
