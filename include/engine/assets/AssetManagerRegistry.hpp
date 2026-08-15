#pragma once
#include <cstdint>

using AssetManagerId = uint32_t;

class AssetManagerRegistry
{
public:
    template <typename T>
    static AssetManagerId getTypeId()
    {
        static const AssetManagerId id = nextId++;
        return id;
    }

private:
    inline static AssetManagerId nextId{};
};
