#pragma once
#include <cstdint>

enum class BufferType : uint8_t
{
    None = 0,
    Vertex = 1 << 0,
    Index = 1 << 1,
    Uniform = 1 << 2,
    Storage = 1 << 3,
    Indirect = 1 << 4,
    TransferSource = 1 << 5,
    TransferDest = 1 << 6
};

enum class BufferMemory : uint8_t
{
    GpuOnly,
    CpuToGpu,
    GpuToCpu
};

enum class BufferUpdateFrequency : uint8_t
{
    Static,
    Dynamic,
    Stream
};

struct BufferDescription
{
    BufferType type = BufferType::None;
    BufferMemory memory = BufferMemory::GpuOnly;
    BufferUpdateFrequency updateFrequency = BufferUpdateFrequency::Static;

    size_t size = 0;
};
