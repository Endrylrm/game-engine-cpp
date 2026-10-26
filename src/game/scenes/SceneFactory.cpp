#include "game/scenes/SceneFactory.hpp"

#include "engine/api/AssetsAPI.hpp"
#include "engine/assets/AssetHandle.hpp"
#include "engine/core/log/Log.hpp"
#include "engine/ecs/components/BoxCollider.hpp"
#include "engine/ecs/components/Renderable.hpp"
#include "engine/ecs/components/Sprite.hpp"
#include "engine/ecs/components/Transform.hpp"
#include "engine/ecs/components/Velocity.hpp"
#include "engine/ecs/entities/EntityBuilder.hpp"
#include "engine/ecs/handle/Entity.hpp"
#include "engine/ecs/registry/systems/SystemStage.hpp"
#include "engine/renderer/resources/Texture.hpp"

#include "game/ecs/components/common/Health.hpp"
#include "game/ecs/components/common/ScreenClamp.hpp"
#include "game/ecs/components/common/Weapon.hpp"
#include "game/ecs/components/player/PlayerInput.hpp"
#include "game/ecs/systems/common/DamageSystem.hpp"
#include "game/ecs/systems/common/DeathSystem.hpp"
#include "game/ecs/systems/common/OutOfBoundsSystem.hpp"
#include "game/ecs/systems/common/ScreenClampSystem.hpp"
#include "game/ecs/systems/common/WeaponCooldownSystem.hpp"
#include "game/ecs/systems/player/PlayerInputSystem.hpp"
#include "game/ecs/systems/player/PlayerMoveSystem.hpp"
#include "game/ecs/systems/player/PlayerShootSystem.hpp"

void SceneFactory::create_menu_scene(Scene &scene)
{
    scene.set_on_load(
        [](Scene &scene)
        {
            LOG_DEBUG("creating Menu Scene...");
            scene.create_entity();
        }
    );
}

void SceneFactory::create_gameplay_scene(Scene &scene)
{
    scene.set_on_load(
        [](Scene &scene)
        {
            LOG_DEBUG("creating Gameplay Scene...");
            scene.get_world().add_system<PlayerInputSystem>(SystemStage::Update);
            scene.get_world().add_system<PlayerMoveSystem>(SystemStage::Update);
            scene.get_world().add_system<WeaponCooldownSystem>(SystemStage::Update);
            scene.get_world().add_system<PlayerShootSystem>(SystemStage::Update);
            scene.get_world().add_system<OutOfBoundsSystem>(SystemStage::Update);
            scene.get_world().add_system<ScreenClampSystem>(SystemStage::PostUpdate);
            scene.get_world().add_system<DamageSystem>(SystemStage::PostUpdate);
            scene.get_world().add_system<DeathSystem>(SystemStage::PostUpdate);
        }
    );

    scene.set_on_unload(
        [](Scene &scene)
        {
            scene.get_world().remove_system<PlayerInputSystem>();
            scene.get_world().remove_system<PlayerMoveSystem>();
            scene.get_world().remove_system<WeaponCooldownSystem>();
            scene.get_world().remove_system<PlayerShootSystem>();
            scene.get_world().remove_system<OutOfBoundsSystem>();
            scene.get_world().remove_system<ScreenClampSystem>();
            scene.get_world().remove_system<DamageSystem>();
            scene.get_world().remove_system<DeathSystem>();
        }
    );
}

void SceneFactory::create_player_scene(Scene &scene)
{
    scene.set_on_load(
        [](Scene &scene)
        {
            LOG_DEBUG("creating Player Scene...");
            AssetHandle<Texture> sprite =
                AssetsAPI::find_or_register<Texture>("assets/player/playerShip1_blue.png");
            AssetsAPI::load<Texture>(sprite);
            Entity player =
                EntityBuilder(scene)
                    .add_component<Transform>(375.0f, 450.0f, 0.0f)
                    .add_component<Velocity>()
                    .add_component<Sprite>(sprite)
                    .add_component<Renderable>()
                    .add_component<Health>(5)
                    .add_component<Weapon>()
                    .add_component<BoxCollider>(Vector2D{99.0f, 75.0f}, Vector2D{0.0f, 0.0f}, false)
                    .add_component<ScreenClamp>(true, true)
                    .add_component<PlayerInput>()
                    .build();

            LOG_DEBUG("Player has Sprite: {}", player.has_component<Sprite>());
        }
    );
}
