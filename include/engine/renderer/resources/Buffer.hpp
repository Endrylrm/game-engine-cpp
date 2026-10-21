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
    ~Buffer();

    BufferHandle getHandle();
    BufferDescription getDescription();

private:
    BufferHandle handle{};
    BufferDescription description{};
    RenderDevice *device = nullptr;
};
