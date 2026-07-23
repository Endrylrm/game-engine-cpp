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
#include "engine/core/events/QueuedEvent.hpp"

class EventBus : public ConnectionSource
{
public:
	template <typename EventType, typename Callback>
	EventConnection connect(Callback &&callback)
	{
		auto &list = listenersMap[typeid(EventType)];

		uint32_t id = currentID++;

		std::function<void(const Event &)> wrapper =
			[fn = std::forward<Callback>(callback)](const Event &e)
		{
			fn(static_cast<const EventType &>(e));
		};

		list.push_back({{id}, std::move(wrapper)});

		return EventConnection(this, typeid(EventType), id);
	}

	template <typename EventType>
	void emit(const EventType &event)
	{
		auto iter = listenersMap.find(typeid(EventType));

		if (iter == listenersMap.end())
			return;

		auto &list = iter->second;

		for (auto &listener : list)
		{
			if (listener.slot.state != ConnectionState::Connected)
				continue;

			listener.callback(event);
		}
	}

	template <typename EventType>
	void dispatch(EventType event)
	{
		eventQueue.push({std::type_index(typeid(EventType)),
						 std::make_unique<EventType>(std::move(event))});
	}

	void processEvents()
	{
		while (!eventQueue.empty())
		{
			auto queued = std::move(eventQueue.front());
			eventQueue.pop();

			auto iter = listenersMap.find(queued->type);

			if (iter == listenersMap.end())
				continue;

			auto &list = iter->second;

			for (auto &listener : list)
			{
				if (listener.slot.state != ConnectionState::Connected)
					continue;

				listener.callback(*queued->event);
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
		auto iter = listenersMap.find(type);

		if (iter == listenersMap.end())
			return;

		auto &list = iter->second;

		for (auto &listener : list)
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
		auto iter = listenersMap.find(type);

		if (iter == listenersMap.end())
			return;

		auto &list = iter->second;

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
		auto iter = listenersMap.find(type);

		if (iter == listenersMap.end())
			return false;

		auto &list = iter->second;

		for (auto &listener : list)
		{
			if (listener.slot.id == id)
			{
				return listener.slot.state == ConnectionState::Connected;
			}
		}
		return false;
	}

	std::unordered_map<std::type_index, std::vector<Listener<const Event &>>> listenersMap{};
	std::queue<std::unique_ptr<QueuedEvent>> eventQueue{};
	uint32_t currentID{};
};
