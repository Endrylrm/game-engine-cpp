#include "game/components/bullet/BulletRenderer.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/api/AssetsAPI.hpp"

void BulletRenderer::onStart()
{
    texture = AssetsAPI::load<Texture>("assets/bullets/laserBlue01.png");
    transform = owner->getComponent<Transform2D>();
}

void BulletRenderer::onRender(Renderer &renderer)
{
    renderer.drawTexture(AssetsAPI::get<Texture>(texture), transform->position.x, transform->position.y);
}
