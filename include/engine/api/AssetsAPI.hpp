#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/assets/AssetDatabase.hpp"
#include "engine/assets/AssetHandle.hpp"

class AssetsAPI : public ManagerAPI<AssetDatabase>
{
public:
    template <typename T>
    static AssetHandle<T> load(const std::string &path)
    {
        return getManager().load<T>(path);
    }

    template <typename T>
    static T *get(AssetHandle<T> id)
    {
        return getManager().get<T>(id);
    }
};