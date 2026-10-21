#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "engine/assets/AssetHandle.hpp"
#include "engine/core/log/Log.hpp"

struct BaseResourceManager
{
    virtual ~BaseResourceManager() = default;
};

template <typename T>
class ResourceManager final : public BaseResourceManager
{
public:
    using Loader = std::function<std::unique_ptr<T>(const std::string &path)>;

    explicit ResourceManager(Loader loader) : loader(std::move(loader)) {}
    ~ResourceManager() override = default;

    T *load(AssetHandle<T> handle, const std::string &path)
    {
        if (auto iter = resources.find(handle); iter != resources.end())
            return iter->second.get();

        std::unique_ptr<T> resource = loader(path);

        if (!resource)
            throw std::runtime_error("Failed to load resource: " + path);

        T *ptr = resource.get();
        resources.emplace(handle, std::move(resource));
        LOG_INFO("Resource loaded in GPU: {}", path);
        return ptr;
    }

    T *get(AssetHandle<T> handle) const
    {
        auto iter = resources.find(handle);

        if (iter == resources.end())
            return nullptr;

        return iter->second.get();
    }

    bool isLoaded(AssetHandle<T> handle) const
    {
        return resources.contains(handle);
    }

    void unload(AssetHandle<T> handle)
    {
        resources.erase(handle);
    }

    void unloadAll()
    {
        resources.clear();
    }

private:
    std::unordered_map<AssetHandle<T>, std::unique_ptr<T>> resources;
    Loader loader;
};
