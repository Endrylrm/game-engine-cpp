#include <algorithm>
#include "game/components/common/ClampLR.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/api/WindowAPI.hpp"

void ClampLR::onStart()
{
    transform = owner->getComponent<Transform2D>();
}

void ClampLR::onPostUpdate()
{
    transform->position.x = std::clamp(transform->position.x, 0.0f, WindowAPI::getWidth() - 99.0f);
}