#pragma once
#include <memory>
#include "engine/entities/Entity.hpp"

class BulletFactory
{
public:
    static std::unique_ptr<Entity> create();
};
