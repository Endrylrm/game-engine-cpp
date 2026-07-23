#pragma once
#include <functional>
#include "engine/api/ManagerAPI.hpp"
#include "engine/core/events/EventBus.hpp"
#include "engine/core/events/Connections.hpp"

class EventsAPI : public ManagerAPI<EventBus>
{
public:
    template <typename EventType, typename Callback>
    static EventConnection connect(Callback &&callback)
    {
        return getManager().connect<EventType>(std::forward<Callback>(callback));
    }

    template <typename EventType>
    static void emit(const EventType &event)
    {
        getManager().emit<EventType>(event);
    }

    template <typename EventType>
    static void dispatch(EventType event)
    {
        getManager().dispatch<EventType>(event);
    }
};