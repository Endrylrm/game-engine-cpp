#include "engine/entities/components/SpriteRenderer.hpp"
#include "engine/scenes/Scene.hpp"

void SpriteRenderer::onAwake()
{
    owner->getScene()->emitEvent(ComponentAddedEvent<SpriteRenderer>{owner, this});
}

void SpriteRenderer::onDestruction()
{
    owner->getScene()->emitEvent(ComponentRemovedEvent<SpriteRenderer>{owner, this});
}