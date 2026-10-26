#pragma once
#include <cstdint>

#include "engine/core/log/Log.hpp"

#include "EventRegistry.hpp"

class ConnectionSource
{
    friend class EventConnection;

public:
    virtual ~ConnectionSource();

protected:
    virtual void disconnect(EventTypeId type, uint32_t id) = 0;
    virtual void set_listener_enabled(EventTypeId type, uint32_t id, bool enabled) = 0;
    virtual bool is_listener_enabled(EventTypeId type, uint32_t id) = 0;

private:
    void register_connection(EventConnection *connection);
    void unregister_connection(EventConnection *connection);

    // intrusive list
    EventConnection *head = nullptr;
};

class EventConnection
{
    friend class ConnectionSource;

public:
    EventConnection() = default;
    EventConnection(ConnectionSource *source, EventTypeId type, uint32_t id)
        : conn_source(source), event_type(type), event_id(id)
    {
        source->register_connection(this);
        LOG_TRACE(
            "Event Connection '{}' constructed at {:p} and connected to source.",
            event_id,
            static_cast<const void *>(this)
        );
    }

    // delete copy
    EventConnection(const EventConnection &) = delete;
    EventConnection &operator=(const EventConnection &) = delete;

    // accepts move semantics
    EventConnection(EventConnection &&other) noexcept
    {
        move_from(other);
        LOG_TRACE(
            "Event Connection '{}' at {:p} moved from {:p}.",
            event_id,
            static_cast<const void *>(this),
            static_cast<const void *>(&other)
        );
    }

    EventConnection &operator=(EventConnection &&other) noexcept
    {
        if (this != &other)
        {
            // clean current connection
            disconnect();
            move_from(other);
        }

        LOG_TRACE(
            "Event Connection '{}' at {:p} moved from {:p}.",
            event_id,
            static_cast<const void *>(this),
            static_cast<const void *>(&other)
        );
        return *this;
    }

    ~EventConnection()
    {
        LOG_TRACE(
            "destroying Event Connection '{}' at {:p}...", event_id, static_cast<const void *>(this)
        );
        disconnect();
    }

    void disconnect()
    {
        if (!conn_source)
            return;

        conn_source->disconnect(event_type, event_id);
        conn_source->unregister_connection(this);
        LOG_TRACE(
            "Event Connection '{}' at {:p} disconnected from source.",
            event_id,
            static_cast<const void *>(this)
        );
        invalidate();
    }

    void enable()
    {
        set_enabled(true);
    }

    void disable()
    {
        set_enabled(false);
    }

    bool is_enabled() const
    {
        return conn_source && conn_source->is_listener_enabled(event_type, event_id);
    }

    bool connected() const
    {
        return conn_source != nullptr;
    }

private:
    void set_enabled(bool enabled)
    {
        if (!conn_source)
            return;

        conn_source->set_listener_enabled(event_type, event_id, enabled);
    }

    void move_from(EventConnection &other)
    {
        conn_source = other.conn_source;
        prev = other.prev;
        next = other.next;
        event_type = other.event_type;
        event_id = other.event_id;

        if (prev)
            prev->next = this;
        else if (conn_source)
            conn_source->head = this;
        if (next)
            next->prev = this;

        // make the other invalid
        other.invalidate();
    }

    void invalidate()
    {
        conn_source = nullptr;
        prev = nullptr;
        next = nullptr;
        event_type = EventRegistry::get_type_id<void>();
        event_id = 0;
    }

    ConnectionSource *conn_source{};
    EventConnection *prev{};
    EventConnection *next{};
    EventTypeId event_type{EventRegistry::get_type_id<void>()};
    uint32_t event_id{};
};

inline ConnectionSource::~ConnectionSource()
{
    EventConnection *cur_connection = head;
    while (cur_connection)
    {
        EventConnection *next = cur_connection->next;
        cur_connection->conn_source = nullptr;
        cur_connection->prev = nullptr;
        cur_connection->next = nullptr;
        cur_connection = next;
    }
}

inline void ConnectionSource::register_connection(EventConnection *connection)
{
    connection->next = head;
    connection->prev = nullptr;
    if (head)
        head->prev = connection;
    head = connection;
}

inline void ConnectionSource::unregister_connection(EventConnection *connection)
{
    if (connection->prev)
        connection->prev->next = connection->next;
    else
        head = connection->next;
    if (connection->next)
        connection->next->prev = connection->prev;
    connection->prev = connection->next = nullptr;
}
