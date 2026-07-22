#pragma once
#include <functional>
#include <typeindex>
#include "engine/core/events/ConnectionSlot.hpp"
#include "engine/core/events/Listener.hpp"
#include "engine/core/events/Connections.hpp"

template <typename... Args>
class Signal : public ConnectionSource
{
public:
	EventConnection connect(std::function<void(Args...)> callback)
	{
		uint32_t id = currentID++;

		slots.push_back({{id}, callback});

		return EventConnection(this, typeid(Signal), id);
	}

	void emit(Args... args)
	{
		for (auto &listener : slots)
		{
			if (listener.slot.state != ConnectionState::Connected)
				continue;

			listener.callback(args...);
		}
	}

	std::size_t slotCount() const
	{
		return slots.size();
	}

private:
	void disconnect(std::type_index type, uint32_t id) override
	{
		for (auto &listener : slots)
		{
			if (listener.slot.id == id)
			{
				listener.slot.state = ConnectionState::Disconnected;
				break;
			}
		}

		cleanup();
	}

	void setListenerEnabled(std::type_index type, uint32_t id, bool enabled) override
	{
		for (auto &listener : slots)
		{
			if (listener.slot.id == id)
			{
				if (listener.slot.state == ConnectionState::Disconnected)
					return;

				listener.slot.state = enabled ? ConnectionState::Connected : ConnectionState::Disabled;
			}
		}
	}

	bool isListenerEnabled(std::type_index type, uint32_t id) override
	{
		for (auto &listener : slots)
		{
			if (listener.slot.id == id)
			{
				return listener.slot.state == ConnectionState::Connected;
			}
		}
		return false;
	}

	void cleanup()
	{
		std::erase_if(slots, [](const Listener<Args...> &listener)
					  { return listener.slot.state == ConnectionState::Disconnected; });
	}

	std::vector<Listener<Args...>> slots{};
	uint32_t currentID{};
};
