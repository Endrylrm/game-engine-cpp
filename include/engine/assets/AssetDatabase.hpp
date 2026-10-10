#pragma once
#include <stdexcept>
#include <string>

#include <engine/assets/managers/AssetManager.hpp>
#include <engine/assets/managers/ResourceManager.hpp>
#include <engine/core/log/TypeName.hpp>

#include "AssetHandle.hpp"
#include "AssetManagerRegistry.hpp"

class AssetDatabase
{
public:
    template <typename T>
    void registerAssetManager()
    {
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();
        assetManagers[id] = std::make_unique<AssetManager<T>>();
    }

    template <typename T>
    void registerResourceManager(typename ResourceManager<T>::Loader loader)
    {
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();
        resourceManagers[id] = std::make_unique<ResourceManager<T>>(std::move(loader));
    }

    // create both the Asset Manager and Resource Manager.
    template <typename T>
    void registerAssetType(typename ResourceManager<T>::Loader loader)
    {
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();
        assetManagers[id] = std::make_unique<AssetManager<T>>();
        resourceManagers[id] = std::make_unique<ResourceManager<T>>(std::move(loader));
    }

    template <typename T>
    AssetHandle<T> findOrRegister(const std::string &path)
    {
        return getAssetManager<T>().load(path);
    }

    template <typename T>
    T *load(AssetHandle<T> handle)
    {
        if (!isLoaded<T>(handle))
        {
            auto &asset = getAssetManager<T>().get(handle);
            return getResourceManager<T>().load(handle, asset.path);
        }

        return getResourceManager<T>().get(handle);
    }

    template <typename T>
    T *get(AssetHandle<T> handle)
    {
        return getResourceManager<T>().get(handle);
    }

    template <typename T>
    bool isLoaded(AssetHandle<T> handle) const
    {
        return getResourceManager<T>().isLoaded(handle);
    }

    template <typename T>
    void unload(AssetHandle<T> handle)
    {
        getResourceManager<T>().unload(handle);
    }

private:
    template <typename T>
    AssetManager<T> &getAssetManager()
    {
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();

        auto iter = assetManagers.find(id);

        if (iter == assetManagers.end())
        {
            throw std::runtime_error(
                std::string("AssetManager<T> not found: ").append(getTypeName<T>())
            );
        }

        return static_cast<AssetManager<T> &>(*iter->second);
    }

    template <typename T>
    const AssetManager<T> &getAssetManager() const
    {
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();

        auto iter = assetManagers.find(id);

        if (iter == assetManagers.end())
        {
            throw std::runtime_error(
                std::string("AssetManager<T> not found: ").append(getTypeName<T>())
            );
        }

        return static_cast<AssetManager<T> &>(*iter->second);
    }

    template <typename T>
    ResourceManager<T> &getResourceManager()
    {
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();

        auto iter = resourceManagers.find(id);

        if (iter == resourceManagers.end())
        {
            throw std::runtime_error(
                std::string("ResourceManager<T> not found: ").append(getTypeName<T>())
            );
        }

        return static_cast<ResourceManager<T> &>(*iter->second);
    }

    template <typename T>
    const ResourceManager<T> &getResourceManager() const
    {
        AssetManagerId id = AssetManagerRegistry::getTypeId<T>();

        auto iter = resourceManagers.find(id);

        if (iter == resourceManagers.end())
        {
            throw std::runtime_error(
                std::string("ResourceManager<T> not found: ").append(getTypeName<T>())
            );
        }

        return static_cast<ResourceManager<T> &>(*iter->second);
    }

    std::unordered_map<AssetManagerId, std::unique_ptr<BaseAssetManager>> assetManagers{};
    std::unordered_map<AssetManagerId, std::unique_ptr<BaseResourceManager>> resourceManagers{};
};
