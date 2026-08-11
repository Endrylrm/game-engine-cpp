#pragma once
#include <cstdint>

using ComponentId = uint32_t;

class ComponentRegistry
{
public:
    template <typename T>
    static ComponentId getTypeId()
    {
        static const ComponentId id = nextId++;
        return id;
    }

private:
    inline static ComponentId nextId{};
};
