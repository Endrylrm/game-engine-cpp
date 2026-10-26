#include "game/SpaceShooterGame.hpp"

#include "engine/api/ScenesAPI.hpp"

#include "game/scenes/SceneFactory.hpp"

void SpaceShooterGame::on_init()
{
    ScenesAPI::register_scene("Menu", SceneFactory::create_menu_scene);
    ScenesAPI::register_scene("Gameplay", SceneFactory::create_gameplay_scene);
    ScenesAPI::register_scene("Player", SceneFactory::create_player_scene);
    ScenesAPI::load_scene("Gameplay");
    ScenesAPI::load_scene_persistent("Player");
}

void SpaceShooterGame::on_shutdown() {}
