#include "game/factories/DirectorFactory.hpp"

#include <engine/core/log/Log.hpp>
#include <engine/entities/EntityBuilder.hpp>

#include <game/managers/GameManager.hpp>

std::unique_ptr<Entity> DirectorFactory::create()
{
    LOG_DEBUG("Director Factory creating...");
    return EntityBuilder{}.name("Director").tag("Director").addComponent<GameManager>().build();
}
