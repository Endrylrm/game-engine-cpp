#pragma once
#include <cstdint>

using SceneId = uint32_t;

class SceneRegistry
{
public:
    template <typename T>
    static SceneId getTypeId()
    {
        static const SceneId id = nextId++;
        return id;
    }

private:
    inline static SceneId nextId{};
};
