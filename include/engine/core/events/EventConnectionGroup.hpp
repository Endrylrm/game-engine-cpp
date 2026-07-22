#pragma once
#include <vector>
#include "engine/core/events/Connections.hpp"

class EventConnectionGroup
{
public:
    void addConnection(EventConnection connection)
    {
        connections.push_back(std::move(connection));
    }

    void disconnectAll()
    {
        connections.clear();
    }

    void setConnectionsEnabled(bool enabled)
    {
        for (auto &connection : connections)
        {
            if (enabled)
            {
                connection.enable();
            }
            else
            {
                connection.disable();
            }
        }
    }

private:
    std::vector<EventConnection> connections{};
};