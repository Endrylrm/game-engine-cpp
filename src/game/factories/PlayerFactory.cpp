#include "game/factories/PlayerFactory.hpp"

#include <engine/api/AssetsAPI.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/core/log/Log.hpp>
#include <engine/entities/EntityBuilder.hpp>
#include <engine/entities/components/SpriteRenderer.hpp>

#include <game/components/common/ClampLR.hpp>
#include <game/components/common/ClampUD.hpp>
#include <game/components/common/Faction.hpp>
#include <game/components/common/Health.hpp>
#include <game/components/player/PlayerController.hpp>

std::unique_ptr<Entity> PlayerFactory::create()
{
    LOG_DEBUG("Player Factory creating...");
    AssetHandle<Texture> sprite = AssetsAPI::load<Texture>("assets/player/playerShip1_blue.png");
    return EntityBuilder{}
        .name("Player")
        .tag("Player")
        .addComponent<Health>(3)
        .addComponent<Faction>(FactionType::Player)
        .addComponent<PlayerController>()
        .addComponent<SpriteRenderer>(sprite)
        .addComponent<ClampLR>()
        .addComponent<ClampUD>()
        .build();
}
