#pragma once
#include <cstdint>

using SystemTypeId = uint32_t;

class SystemRegistry
{
public:
    template <typename T>
    static SystemTypeId get_type_id()
    {
        static const SystemTypeId id = next_id++;
        return id;
    }

private:
    inline static SystemTypeId next_id{};
};
