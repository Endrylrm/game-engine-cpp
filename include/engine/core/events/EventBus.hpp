#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>
#include <typeindex>
#include <memory>
#include <algorithm>
#include "engine/core/events/ConnectionSlot.hpp"
#include "engine/core/events/Event.hpp"
#include "engine/core/events/Listener.hpp"
#include "engine/core/events/Connections.hpp"

class EventBus : public ConnectionSource
{
public:
	template <typename EventType>
	EventConnection connect(std::function<void(const EventType &)> callback)
	{
		auto &list = listenersMap[typeid(EventType)];

		uint32_t id = currentID++;

		list.push_back({{id}, [fn = std::move(callback)](const Event &e)
						{
							fn(static_cast<const EventType &>(e));
						}});

		return EventConnection(this, EventType, id);
	}

	template <typename EventType>
	void emit(const EventType &event)
	{
		auto it = listenersMap.find(typeid(EventType));

		if (it == listenersMap.end())
			return;

		for (auto &listener : it->second)
		{
			if (listener.slot.state != ConnectionState::Connected)
				continue;

			listener.callback(event);
		}
	}

	template <typename EventType>
	void dispatch(EventType event)
	{
		eventQueue.push(std::make_unique<EventType>(std::move(event)));
	}

	void processEvents()
	{
		while (!eventQueue.empty())
		{
			auto event = std::move(eventQueue.front());
			eventQueue.pop();

			auto it = listenersMap.find(typeid(*event));

			if (it == listenersMap.end())
				continue;

			for (auto &listener : it->second)
			{
				if (listener.slot.state != ConnectionState::Connected)
					continue;

				listener.callback(*event);
			}
		}
	}

	void removeDeletedEvents()
	{
		for (auto &[type, list] : listenersMap)
		{
			std::erase_if(list, [](const Listener<const Event &> &listener)
						  { return listener.slot.state == ConnectionState::Disconnected; });
		}
	}

private:
	void disconnect(std::type_index type, uint32_t id) override
	{
		auto it = listenersMap.find(type);

		if (it == listenersMap.end())
			return;

		for (auto &listener : it->second)
		{
			if (listener.slot.id == id)
			{
				listener.slot.state = ConnectionState::Disconnected;
				return;
			}
		}
	}

	void setListenerEnabled(std::type_index type, uint32_t id, bool enabled) override
	{
		auto it = listenersMap.find(type);

		if (it == listenersMap.end())
			return;

		auto &list = it->second;

		for (auto &listener : list)
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
		auto it = listenersMap.find(type);

		if (it == listenersMap.end())
			return;

		auto &list = it->second;

		for (auto &listener : list)
		{
			if (listener.slot.id == id)
			{
				return listener.slot.state == ConnectionState::Connected;
			}
		}
		return false;
	}

	std::unordered_map<std::type_index, std::vector<Listener<const Event &>>> listenersMap;
	std::queue<std::unique_ptr<Event>> eventQueue;
	uint32_t currentID = 0;
};
