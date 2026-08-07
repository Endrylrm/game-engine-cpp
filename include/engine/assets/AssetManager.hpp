#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <engine/core/log/Log.hpp>

#include "AssetHandle.hpp"

struct BaseAssetManager
{
    virtual ~BaseAssetManager() = default;
};

template <typename T>
class AssetManager : public BaseAssetManager
{
public:
    using Loader = std::function<std::unique_ptr<T>(const std::string &path)>;

    explicit AssetManager(Loader loader) : loader(std::move(loader)) {}
    ~AssetManager() override = default;

    AssetHandle<T> load(const std::string &path)
    {
        if (auto it = pathToHandle.find(path); it != pathToHandle.end())
            return it->second;

        AssetHandle<T> handle(nextID++);
        assets[handle] = std::move(loader(path));
        LOG_INFO("loaded Asset: {}", path);
        pathToHandle[path] = handle;
        return handle;
    }

    T *get(AssetHandle<T> handle) const
    {
        return assets.at(handle).get();
    }

private:
    std::unordered_map<AssetHandle<T>, std::unique_ptr<T>, AssetHandleHasher> assets;
    std::unordered_map<std::string, AssetHandle<T>> pathToHandle;
    uint32_t nextID{1};
    Loader loader;
};
