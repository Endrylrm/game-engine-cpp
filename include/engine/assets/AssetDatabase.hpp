#pragma once
#include <typeindex>
#include <string>
#include <stdexcept>
#include "engine/assets/AssetManager.hpp"
#include "engine/assets/AssetHandle.hpp"

class AssetDatabase
{
public:
    template <typename T>
    void registerManager(typename AssetManager<T>::Loader loader)
    {
        managers[typeid(T)] = std::make_unique<AssetManager<T>>(std::move(loader));
    }

    template <typename T>
    AssetHandle<T> load(const std::string &path)
    {
        return getManager<T>().load(path);
    }

    template <typename T>
    T *get(AssetHandle<T> handle)
    {
        return getManager<T>().get(handle);
    }

    template <typename T>
    AssetManager<T> &getManager()
    {
        auto iter = managers.find(typeid(T));
        if (iter == managers.end())
            throw std::runtime_error("AssetManager<T> not found: " + std::string(typeid(T).name()));

        return static_cast<AssetManager<T> &>(*iter->second);
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<BaseAssetManager>> managers{};
};