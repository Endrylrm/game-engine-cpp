#include "game/factories/BulletFactory.hpp"
#include "game/components/common/Faction.hpp"
#include "game/components/common/Health.hpp"
#include "game/components/bullet/BulletMove.hpp"
#include "game/components/bullet/BulletDeleter.hpp"
#include "engine/entities/EntityBuilder.hpp"
#include "engine/entities/components/SpriteRenderer.hpp"
#include "engine/api/AssetsAPI.hpp"
#include "engine/core/graphics/Texture.hpp"

std::unique_ptr<Entity> BulletFactory::create()
{
    AssetHandle<Texture> sprite = AssetsAPI::load<Texture>("assets/bullets/laserBlue01.png");
    return EntityBuilder{}
        .tag("Player")
        .addComponent<Health>(1)
        .addComponent<Faction>(FactionType::Player)
        .addComponent<BulletMove>()
        .addComponent<BulletDeleter>()
        .addComponent<SpriteRenderer>(sprite)
        .build();
}
