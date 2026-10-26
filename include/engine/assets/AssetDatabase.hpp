#pragma once
#include <stdexcept>
#include <string>

#include "engine/assets/managers/AssetManager.hpp"
#include "engine/assets/managers/ResourceManager.hpp"
#include "engine/core/log/TypeName.hpp"

#include "AssetHandle.hpp"
#include "AssetManagerRegistry.hpp"

class AssetDatabase
{
public:
    template <typename T>
    void register_asset_manager()
    {
        AssetManagerId id = AssetManagerRegistry::get_type_id<T>();
        asset_managers[id] = std::make_unique<AssetManager<T>>();
    }

    template <typename T>
    void register_resource_manager(typename ResourceManager<T>::Loader loader)
    {
        AssetManagerId id = AssetManagerRegistry::get_type_id<T>();
        resource_managers[id] = std::make_unique<ResourceManager<T>>(std::move(loader));
    }

    // create both the Asset Manager and Resource Manager.
    template <typename T>
    void register_asset_type(typename ResourceManager<T>::Loader loader)
    {
        AssetManagerId id = AssetManagerRegistry::get_type_id<T>();
        asset_managers[id] = std::make_unique<AssetManager<T>>();
        resource_managers[id] = std::make_unique<ResourceManager<T>>(std::move(loader));
    }

    template <typename T>
    AssetHandle<T> find_or_register(const std::string &path)
    {
        return get_asset_manager<T>().load(path);
    }

    template <typename T>
    T *load(AssetHandle<T> handle)
    {
        if (!is_loaded<T>(handle))
        {
            auto &asset = get_asset_manager<T>().get(handle);
            return get_resource_manager<T>().load(handle, asset.path);
        }

        return get_resource_manager<T>().get(handle);
    }

    template <typename T>
    T *get(AssetHandle<T> handle)
    {
        return get_resource_manager<T>().get(handle);
    }

    template <typename T>
    bool is_loaded(AssetHandle<T> handle) const
    {
        return get_resource_manager<T>().is_loaded(handle);
    }

    template <typename T>
    void unload(AssetHandle<T> handle)
    {
        get_resource_manager<T>().unload(handle);
    }

private:
    template <typename T>
    AssetManager<T> &get_asset_manager()
    {
        AssetManagerId id = AssetManagerRegistry::get_type_id<T>();

        auto iter = asset_managers.find(id);

        if (iter == asset_managers.end())
        {
            throw std::runtime_error(
                std::string("AssetManager<T> not found: ").append(get_type_name<T>())
            );
        }

        return static_cast<AssetManager<T> &>(*iter->second);
    }

    template <typename T>
    const AssetManager<T> &get_asset_manager() const
    {
        AssetManagerId id = AssetManagerRegistry::get_type_id<T>();

        auto iter = asset_managers.find(id);

        if (iter == asset_managers.end())
        {
            throw std::runtime_error(
                std::string("AssetManager<T> not found: ").append(get_type_name<T>())
            );
        }

        return static_cast<AssetManager<T> &>(*iter->second);
    }

    template <typename T>
    ResourceManager<T> &get_resource_manager()
    {
        AssetManagerId id = AssetManagerRegistry::get_type_id<T>();

        auto iter = resource_managers.find(id);

        if (iter == resource_managers.end())
        {
            throw std::runtime_error(
                std::string("ResourceManager<T> not found: ").append(get_type_name<T>())
            );
        }

        return static_cast<ResourceManager<T> &>(*iter->second);
    }

    template <typename T>
    const ResourceManager<T> &get_resource_manager() const
    {
        AssetManagerId id = AssetManagerRegistry::get_type_id<T>();

        auto iter = resource_managers.find(id);

        if (iter == resource_managers.end())
        {
            throw std::runtime_error(
                std::string("ResourceManager<T> not found: ").append(get_type_name<T>())
            );
        }

        return static_cast<ResourceManager<T> &>(*iter->second);
    }

    std::unordered_map<AssetManagerId, std::unique_ptr<BaseAssetManager>> asset_managers{};
    std::unordered_map<AssetManagerId, std::unique_ptr<BaseResourceManager>> resource_managers{};
};
