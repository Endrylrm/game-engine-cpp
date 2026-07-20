#include "game/factories/PlayerFactory.hpp"
#include "game/components/common/ClampLR.hpp"
#include "game/components/common/ClampUD.hpp"
#include "game/components/common/Faction.hpp"
#include "game/components/common/Health.hpp"
#include "game/components/player/PlayerController.hpp"
#include "engine/entities/EntityBuilder.hpp"
#include "engine/entities/components/SpriteRenderer.hpp"
#include "engine/api/AssetsAPI.hpp"
#include "engine/core/graphics/Texture.hpp"

std::unique_ptr<Entity> PlayerFactory::create()
{
    AssetHandle<Texture> sprite = AssetsAPI::load<Texture>("assets/player/playerShip1_blue.png");
    return EntityBuilder{}
        .tag("Player")
        .addComponent<Health>(3)
        .addComponent<Faction>(FactionType::Player)
        .addComponent<PlayerController>()
        .addComponent<SpriteRenderer>(sprite)
        .addComponent<ClampLR>()
        .addComponent<ClampUD>()
        .build();
}
