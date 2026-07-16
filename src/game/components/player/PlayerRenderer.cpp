#include "game/components/player/PlayerRenderer.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/api/AssetsAPI.hpp"

void PlayerRenderer::onStart()
{
    texture = AssetsAPI::load<Texture>("assets/player/playerShip1_blue.png");
    transform = owner->getComponent<Transform2D>();
}

void PlayerRenderer::onRender(Renderer &renderer)
{
    renderer.drawTexture(AssetsAPI::get<Texture>(texture), transform->position.x, transform->position.y);
}