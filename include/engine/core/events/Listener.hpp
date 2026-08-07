#pragma once
#include <functional>

#include "ConnectionSlot.hpp"

template <typename... Args>
struct Listener
{
    ConnectionSlot slot;
    std::function<void(Args...)> callback;
};
