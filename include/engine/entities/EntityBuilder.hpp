#pragma once
#include <memory>
#include <string_view>

#include "engine/entities/Entity.hpp"
#include "engine/entities/components/Component.hpp"

class EntityBuilder
{
public:
    template <std::derived_from<Component> T, typename... Args>
    EntityBuilder &addComponent(Args &&...args)
    {
        entity->addComponent<T>(std::forward<Args>(args)...);
        return *this;
    }

    EntityBuilder &name(std::string_view name)
    {
        entity->name = std::move(name);
        return *this;
    }

    EntityBuilder &tag(std::string_view tag)
    {
        entity->tag = std::move(tag);
        return *this;
    }

    std::unique_ptr<Entity> build()
    {
        return std::move(entity);
    }

private:
    std::unique_ptr<Entity> entity{std::make_unique<Entity>()};
};