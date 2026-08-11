#pragma once
#include <cstdint>

using SystemTypeId = uint32_t;

class SystemRegistry
{
public:
    template <typename T>
    static SystemTypeId getTypeId()
    {
        static const SystemTypeId id = nextId++;
        return id;
    }

private:
    inline static SystemTypeId nextId{};
};
