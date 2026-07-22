#pragma once
#include <cstddef>

using ComponentId = std::size_t;

class ComponentRegistry
{
public:
    template <typename T>
    static ComponentId GetId()
    {
        static const ComponentId id = nextId++;
        return id;
    }

private:
    inline static ComponentId nextId{};
};
