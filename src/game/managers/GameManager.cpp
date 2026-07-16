#include "game/managers/GameManager.hpp"
#include "game/components/common/Health.hpp"
#include "game/factories/PlayerFactory.hpp"
#include "engine/api/EntityAPI.hpp"
#include "engine/api/TimerAPI.hpp"

void GameManager::onStart()
{
	respawnPlayer();
}

void GameManager::onUpdate(float deltaTime)
{
}

void GameManager::respawnPlayer()
{
	player = EntityAPI::spawnFromBlueprint(PlayerFactory::create());
	Health *health = player->getComponent<Health>();
	playerDiedConnection = health->onDead.connect([this]()
												  { TimerAPI::after(1.5f, [this]()
																	{ respawnPlayer(); }); });
}