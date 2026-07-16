#pragma once
#include <functional>
#include "engine/core/events/ConnectionSlot.hpp"

template <typename... Args>
struct Listener
{
	ConnectionSlot slot;
	std::function<void(Args...)> callback;
};
