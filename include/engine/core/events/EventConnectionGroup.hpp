#pragma once
#include <vector>

#include "Connections.hpp"

class EventConnectionGroup
{
public:
    void add_connection(EventConnection connection)
    {
        connections.push_back(std::move(connection));
    }

    void disconnect_all()
    {
        connections.clear();
    }

    void set_connections_enabled(bool enabled)
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