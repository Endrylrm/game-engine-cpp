#pragma once
#include "engine/renderer/RenderDevice.hpp"
#include "engine/renderer/containers/ResourceHandle.hpp"
#include "engine/renderer/descriptions/Buffer.hpp"

class Buffer
{
public:
    Buffer(BufferHandle handle, BufferDescription description, RenderDevice *device)
        : handle(handle), description(description), device(device)
    {
    }
    ~Buffer() = default;

    bool is_valid() const
    {
        return device->valid_buffer(handle);
    }

    BufferHandle get_handle() const
    {
        return handle;
    }

    const BufferDescription &get_description() const
    {
        return description;
    }

private:
    BufferHandle handle{};
    BufferDescription description{};
    RenderDevice *device = nullptr;
};
