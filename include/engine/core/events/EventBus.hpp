#pragma once
#include <algorithm>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <engine/core/log/Log.hpp>

#include "ConnectionSlot.hpp"
#include "Connections.hpp"
#include "Event.hpp"
#include "EventRegistry.hpp"
#include "Listener.hpp"
#include "QueuedEvent.hpp"

class EventBus : public ConnectionSource
{
public:
    template <typename EventType, typename Callback>
    EventConnection connect(Callback &&callback)
    {
        auto &list = listenersMap[EventRegistry::getTypeId<EventType>()];

        uint32_t id = currentID++;

        std::function<void(const Event &)> wrapper =
            [fn = std::forward<Callback>(callback)](const Event &e)
        { fn(static_cast<const EventType &>(e)); };

        list.push_back({{id}, std::move(wrapper)});
        LOG_DEBUG("Event id '{}' connected to EventBus.", id);

        return EventConnection(this, EventRegistry::getTypeId<EventType>(), id);
    }

    template <typename EventType>
    void emit(const EventType &event)
    {
        auto iter = listenersMap.find(EventRegistry::getTypeId<EventType>());

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
        pendingEvents.push_back(
            {EventRegistry::getTypeId<EventType>(), std::make_unique<EventType>(std::move(event))}
        );
    }

    void processEvents()
    {
        std::swap(eventQueue, pendingEvents);

        if (eventQueue.empty())
            return;

        for (auto &event : eventQueue)
        {
            auto queued = std::move(event);

            auto iter = listenersMap.find(queued.type);

            if (iter == listenersMap.end())
                continue;

            auto &list = iter->second;

            for (auto &listener : list)
            {
                if (listener.slot.state != ConnectionState::Connected)
                    continue;

                listener.callback(*queued.event);
            }
        }

        eventQueue.clear();
    }

    void removeDeletedEvents()
    {
        for (auto &[type, list] : listenersMap)
        {
            std::erase_if(
                list,
                [](const Listener<const Event &> &listener)
                { return listener.slot.state == ConnectionState::Disconnected; }
            );
        }
    }

private:
    void disconnect(EventTypeId type, uint32_t id) override
    {
        auto iter = listenersMap.find(type);

        if (iter == listenersMap.end())
            return;

        auto &list = iter->second;

        for (auto &listener : list)
        {
            if (listener.slot.id == id)
            {
                LOG_DEBUG("Event id '{}' disconnected from EventBus.", id);
                listener.slot.state = ConnectionState::Disconnected;
                return;
            }
        }
    }

    void setListenerEnabled(EventTypeId type, uint32_t id, bool enabled) override
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

                listener.slot.state =
                    enabled ? ConnectionState::Connected : ConnectionState::Disabled;
            }
        }
    }

    bool isListenerEnabled(EventTypeId type, uint32_t id) override
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

    std::unordered_map<EventTypeId, std::vector<Listener<const Event &>>> listenersMap{};
    std::vector<QueuedEvent> eventQueue{};
    std::vector<QueuedEvent> pendingEvents{};
    uint32_t currentID{};
};
