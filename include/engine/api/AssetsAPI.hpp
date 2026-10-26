#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/assets/AssetDatabase.hpp"
#include "engine/assets/AssetHandle.hpp"

class AssetsAPI : public ManagerAPI<AssetDatabase>
{
public:
    template <typename T>
    static AssetHandle<T> find_or_register(const std::string &path)
    {
        return get_manager().find_or_register<T>(path);
    }

    template <typename T>
    static T *load(AssetHandle<T> handle)
    {
        return get_manager().load<T>(handle);
    }

    template <typename T>
    static T *get(AssetHandle<T> handle)
    {
        return get_manager().get<T>(handle);
    }

    template <typename T>
    static bool is_loaded(AssetHandle<T> handle)
    {
        return get_manager().is_loaded<T>(handle);
    }

    template <typename T>
    static void unload(AssetHandle<T> handle)
    {
        return get_manager().unload<T>(handle);
    }
};
