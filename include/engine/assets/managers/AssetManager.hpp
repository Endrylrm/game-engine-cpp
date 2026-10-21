#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include "engine/assets/AssetHandle.hpp"
#include "engine/core/log/Log.hpp"

template <typename T>
struct AssetRecord
{
    std::string path;
};

struct BaseAssetManager
{
    virtual ~BaseAssetManager() = default;
};

template <typename T>
class AssetManager final : public BaseAssetManager
{
public:
    ~AssetManager() override = default;

    AssetHandle<T> load(const std::string &path)
    {
        if (auto iter = pathToHandle.find(path); iter != pathToHandle.end())
            return iter->second;

        AssetHandle<T> handle(nextID++);
        assets.emplace(handle, AssetRecord<T>{.path = path});
        pathToHandle.emplace(path, handle);
        LOG_INFO("loaded Asset: {}", path);
        return handle;
    }

    AssetHandle<T> find(const std::string &path) const
    {
        auto iter = pathToHandle.find(path);

        if (iter == pathToHandle.end())
            return {};

        return iter->second;
    }

    const AssetRecord<T> &get(AssetHandle<T> handle) const
    {
        auto iter = assets.find(handle);

        if (iter == assets.end())
            throw std::runtime_error("AssetHandle not found");

        return iter->second;
    }

    bool exists(AssetHandle<T> handle) const
    {
        return assets.contains(handle);
    }

    void unregister(AssetHandle<T> handle)
    {
        auto iter = assets.find(handle);

        if (iter == assets.end())
            return;

        pathToHandle.erase(iter->second.path);
        assets.erase(iter);
    }

private:
    std::unordered_map<AssetHandle<T>, AssetRecord<T>> assets;
    std::unordered_map<std::string, AssetHandle<T>> pathToHandle;
    uint32_t nextID{1};
};
