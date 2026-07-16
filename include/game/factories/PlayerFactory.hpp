#pragma once
#include <memory>
#include "engine/entities/Entity.hpp"

class PlayerFactory
{
public:
    static std::unique_ptr<Entity> create();
};
