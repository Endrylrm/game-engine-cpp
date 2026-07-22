#pragma once
#include <cstdint>
#include <functional>

template <typename T>
class AssetHandle
{
public:
    AssetHandle() = default;
    explicit AssetHandle(uint32_t id) : id(id) {}

    uint32_t getID() const
    {
        return id;
    }

    bool isValid() const
    {
        return id != 0;
    }

    void reset()
    {
        id = 0;
    }

    bool operator==(const AssetHandle &other) const
    {
        return id == other.id;
    }

    bool operator!=(const AssetHandle &other) const
    {
        return id != other.id;
    }

private:
    uint32_t id{};
};

struct AssetHandleHasher
{
    template <typename T>
    size_t operator()(const AssetHandle<T> &handle) const noexcept
    {
        return std::hash<uint32_t>{}(handle.getID());
    }
};
