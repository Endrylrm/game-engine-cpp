#include "engine/ecs/systems/RenderSystem.hpp"

#include <engine/api/AssetsAPI.hpp>
#include <engine/ecs/components/Renderable.hpp>
#include <engine/ecs/components/Sprite.hpp>
#include <engine/ecs/components/Transform.hpp>
#include <engine/renderer/resources/Texture.hpp>

void RenderSystem::onRender(World &world, Renderer &renderer)
{
    for (auto [sprite, transform, _] : world.view<Sprite, Transform, Renderable>())
    {
        auto *texture = AssetsAPI::get<Texture>(sprite.textureId);
        renderer.getSpriteRenderer().drawTexture(texture, transform.position);
    }
}
