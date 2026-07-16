#include <algorithm>
#include "game/components/common/ClampUD.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/api/WindowAPI.hpp"

void ClampUD::onStart()
{
    transform = owner->getComponent<Transform2D>();
}

void ClampUD::onPostUpdate()
{
    transform->position.y = std::clamp(transform->position.y, 0.0f, WindowAPI::getHeight() - 75.0f);
}