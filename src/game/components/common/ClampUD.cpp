#include "game/components/common/ClampUD.hpp"

#include <algorithm>

#include <engine/api/WindowAPI.hpp>
#include <engine/entities/Entity.hpp>

void ClampUD::onStart()
{
    transform = owner->getComponent<Transform>();
}

void ClampUD::onPostUpdate()
{
    transform->position.y = std::clamp(transform->position.y, 0.0f, WindowAPI::getHeight() - 75.0f);
}