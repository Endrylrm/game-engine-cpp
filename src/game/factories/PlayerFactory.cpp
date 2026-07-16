#include "game/factories/PlayerFactory.hpp"
#include "game/components/common/ClampLR.hpp"
#include "game/components/common/ClampUD.hpp"
#include "game/components/common/Faction.hpp"
#include "game/components/common/Health.hpp"
#include "game/components/player/PlayerController.hpp"
#include "game/components/player/PlayerRenderer.hpp"
#include "engine/entities/EntityBuilder.hpp"

std::unique_ptr<Entity> PlayerFactory::create()
{
    return EntityBuilder{}
        .tag("Player")
        .addComponent<Health>(3)
        .addComponent<Faction>(FactionType::Player)
        .addComponent<PlayerController>()
        .addComponent<PlayerRenderer>()
        .addComponent<ClampLR>()
        .addComponent<ClampUD>()
        .build();
}
