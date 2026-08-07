#include "game/components/common/ClampLR.hpp"

#include <algorithm>

#include <engine/api/WindowAPI.hpp>
#include <engine/entities/Entity.hpp>

void ClampLR::onStart()
{
    transform = owner->getComponent<Transform>();
}

void ClampLR::onPostUpdate()
{
    transform->position.x = std::clamp(transform->position.x, 0.0f, WindowAPI::getWidth() - 99.0f);
}