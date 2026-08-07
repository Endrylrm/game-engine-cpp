#include "engine/entities/components/SpriteRenderer.hpp"

#include <engine/core/log/Log.hpp>
#include <engine/scenes/Scene.hpp>

void SpriteRenderer::onAwake()
{
    owner->getScene()->emitEvent(ComponentAddedEvent<SpriteRenderer>{owner, this});
    LOG_DEBUG("Registered to render system!");
}

void SpriteRenderer::onDestruction()
{
    owner->getScene()->emitEvent(ComponentRemovedEvent<SpriteRenderer>{owner, this});
    LOG_DEBUG("Unregistered from render system!");
}