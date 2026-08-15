#pragma once
#include <stdexcept>
#include <string>

#include <engine/core/log/TypeName.hpp>

#include "AssetHandle.hpp"
#include "AssetManager.hpp"
#include "AssetManagerRegistry.hpp"

class AssetDatabase
{
public:
    template <typename T>
    void registerManager(typename AssetManager<T>::Loader loader)
    {
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();
        managers[id] = std::make_unique<AssetManager<T>>(std::move(loader));
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
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();

        auto iter = managers.find(id);
        if (iter == managers.end())
        {
            throw std::runtime_error(
                std::string("AssetManager<T> not found: ").append(getTypeName<T>())
            );
        }

        return static_cast<AssetManager<T> &>(*iter->second);
    }

private:
    std::unordered_map<AssetManagerId, std::unique_ptr<BaseAssetManager>> managers{};
};
