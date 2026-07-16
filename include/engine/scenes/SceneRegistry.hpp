#pragma once
#include <cstddef>

using SceneId = std::size_t;

class SceneRegistry
{
public:
    template <typename T>
    static SceneId GetId()
    {
        static const SceneId id = nextId++;
        return id;
    }

private:
    inline static SceneId nextId = 0;
};
