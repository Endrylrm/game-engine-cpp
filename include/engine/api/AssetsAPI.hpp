#pragma once
#include <engine/api/ManagerAPI.hpp>
#include <engine/assets/AssetDatabase.hpp>
#include <engine/assets/AssetHandle.hpp>

class AssetsAPI : public ManagerAPI<AssetDatabase>
{
public:
    template <typename T>
    static AssetHandle<T> findOrRegister(const std::string &path)
    {
        return getManager().findOrRegister<T>(path);
    }

    template <typename T>
    static T *load(AssetHandle<T> handle)
    {
        return getManager().load<T>(handle);
    }

    template <typename T>
    static T *get(AssetHandle<T> handle)
    {
        return getManager().get<T>(handle);
    }

    template <typename T>
    static bool isLoaded(AssetHandle<T> handle)
    {
        return getManager().isLoaded<T>(handle);
    }

    template <typename T>
    static void unload(AssetHandle<T> handle)
    {
        return getManager().unload<T>(handle);
    }
};
