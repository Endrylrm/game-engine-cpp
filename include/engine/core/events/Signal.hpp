#pragma once
#include <functional>

#include <engine/core/log/Log.hpp>

#include "ConnectionSlot.hpp"
#include "Connections.hpp"
#include "EventRegistry.hpp"
#include "Listener.hpp"

template <typename... Args>
class Signal : public ConnectionSource
{
public:
    EventConnection connect(std::function<void(Args...)> callback)
    {
        uint32_t id = currentID++;

        slots.push_back({{id}, callback});
        LOG_DEBUG("Event id '{}' connected to Signal.", id);

        return EventConnection(this, EventRegistry::getTypeId<Signal>(), id);
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
    void disconnect(EventTypeId type, uint32_t id) override
    {
        for (auto &listener : slots)
        {
            if (listener.slot.id == id)
            {
                LOG_DEBUG("Event id '{}' disconnected from Signal.", id);
                listener.slot.state = ConnectionState::Disconnected;
                break;
            }
        }

        cleanup();
    }

    void setListenerEnabled(EventTypeId type, uint32_t id, bool enabled) override
    {
        for (auto &listener : slots)
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
        std::erase_if(
            slots,
            [](const Listener<Args...> &listener)
            { return listener.slot.state == ConnectionState::Disconnected; }
        );
    }

    std::vector<Listener<Args...>> slots{};
    uint32_t currentID{};
};
