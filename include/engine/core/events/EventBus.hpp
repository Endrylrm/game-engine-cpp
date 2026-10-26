#pragma once
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "engine/core/log/Log.hpp"

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
        auto &list = listeners_map[EventRegistry::get_type_id<EventType>()];

        uint32_t id = current_id++;

        std::function<void(const Event &)> wrapper =
            [fn = std::forward<Callback>(callback)](const Event &e)
        { fn(static_cast<const EventType &>(e)); };

        list.push_back({{id}, std::move(wrapper)});
        LOG_DEBUG("Event id '{}' connected to EventBus.", id);

        return EventConnection(this, EventRegistry::get_type_id<EventType>(), id);
    }

    template <typename EventType>
    void emit(const EventType &event)
    {
        auto iter = listeners_map.find(EventRegistry::get_type_id<EventType>());

        if (iter == listeners_map.end())
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
        pending_events.push_back(
            {EventRegistry::get_type_id<EventType>(), std::make_unique<EventType>(std::move(event))}
        );
    }

    void process_events()
    {
        std::swap(event_queue, pending_events);

        if (event_queue.empty())
            return;

        for (auto &event : event_queue)
        {
            auto queued = std::move(event);

            auto iter = listeners_map.find(queued.type);

            if (iter == listeners_map.end())
                continue;

            auto &list = iter->second;

            for (auto &listener : list)
            {
                if (listener.slot.state != ConnectionState::Connected)
                    continue;

                listener.callback(*queued.event);
            }
        }

        event_queue.clear();
    }

    void remove_deleted_events()
    {
        for (auto &[TYPE, list] : listeners_map)
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
        auto iter = listeners_map.find(type);

        if (iter == listeners_map.end())
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

    void set_listener_enabled(EventTypeId type, uint32_t id, bool enabled) override
    {
        auto iter = listeners_map.find(type);

        if (iter == listeners_map.end())
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

    bool is_listener_enabled(EventTypeId type, uint32_t id) override
    {
        auto iter = listeners_map.find(type);

        if (iter == listeners_map.end())
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

    std::unordered_map<EventTypeId, std::vector<Listener<const Event &>>> listeners_map{};
    std::vector<QueuedEvent> event_queue{};
    std::vector<QueuedEvent> pending_events{};
    uint32_t current_id{};
};
