#pragma once
#include <cstdint>

enum class ConnectionState
{
    Connected,
    Disabled,
    Disconnected
};

struct ConnectionSlot
{
    uint32_t id;
    ConnectionState state = ConnectionState::Connected;
};