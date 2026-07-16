#include "game/factories/BulletFactory.hpp"
#include "game/components/common/Faction.hpp"
#include "game/components/common/Health.hpp"
#include "game/components/bullet/BulletRenderer.hpp"
#include "game/components/bullet/BulletMove.hpp"
#include "game/components/bullet/BulletDeleter.hpp"
#include "engine/entities/EntityBuilder.hpp"

std::unique_ptr<Entity> BulletFactory::create()
{
    return EntityBuilder{}
        .tag("Player")
        .addComponent<Health>(1)
        .addComponent<Faction>(FactionType::Player)
        .addComponent<BulletMove>()
        .addComponent<BulletDeleter>()
        .addComponent<BulletRenderer>()
        .build();
}
