#pragma once
#include <memory>

#include "engine/entities/Entity.hpp"

class DirectorFactory
{
public:
    static std::unique_ptr<Entity> create();
};
