#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/core/events/Connections.hpp"
#include "engine/core/events/EventBus.hpp"

class EventsAPI : public ManagerAPI<EventBus>
{
public:
    template <typename EventType, typename Callback>
    static EventConnection connect(Callback &&callback)
    {
        return get_manager().connect<EventType>(std::forward<Callback>(callback));
    }

    template <typename EventType>
    static void emit(const EventType &event)
    {
        get_manager().emit<EventType>(event);
    }

    template <typename EventType>
    static void dispatch(EventType event)
    {
        get_manager().dispatch<EventType>(event);
    }
};
