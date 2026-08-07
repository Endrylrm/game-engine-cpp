#pragma once
#include <cstdint>

#include "engine/core/events/EventRegistry.hpp"
#include "engine/core/log/Log.hpp"

class ConnectionSource
{
    friend class EventConnection;

public:
    virtual ~ConnectionSource();

protected:
    virtual void disconnect(EventTypeId type, uint32_t id) = 0;
    virtual void setListenerEnabled(EventTypeId type, uint32_t id, bool enabled) = 0;
    virtual bool isListenerEnabled(EventTypeId type, uint32_t id) = 0;

private:
    void registerConnection(EventConnection *connection);
    void unregisterConnection(EventConnection *connection);

    // intrusive list
    EventConnection *head = nullptr;
};

class EventConnection
{
    friend class ConnectionSource;

public:
    EventConnection() = default;
    EventConnection(ConnectionSource *source, EventTypeId type, uint32_t id)
        : connSource(source), eventType(type), eventId(id)
    {
        source->registerConnection(this);
        LOG_TRACE(
            "Event Connection '{}' constructed at {:p} and connected to source.",
            eventId,
            static_cast<const void *>(this)
        );
    }

    // delete copy
    EventConnection(const EventConnection &) = delete;
    EventConnection &operator=(const EventConnection &) = delete;

    // accepts move semantics
    EventConnection(EventConnection &&other) noexcept
    {
        moveFrom(other);
        LOG_TRACE(
            "Event Connection '{}' at {:p} moved from {:p}.",
            eventId,
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
            moveFrom(other);
        }

        LOG_TRACE(
            "Event Connection '{}' at {:p} moved from {:p}.",
            eventId,
            static_cast<const void *>(this),
            static_cast<const void *>(&other)
        );
        return *this;
    }

    ~EventConnection()
    {
        LOG_TRACE(
            "destroying Event Connection '{}' at {:p}...", eventId, static_cast<const void *>(this)
        );
        disconnect();
    }

    void disconnect()
    {
        if (!connSource)
            return;

        connSource->disconnect(eventType, eventId);
        connSource->unregisterConnection(this);
        LOG_TRACE(
            "Event Connection '{}' at {:p} disconnected from source.",
            eventId,
            static_cast<const void *>(this)
        );
        invalidate();
    }

    void enable()
    {
        setEnabled(true);
    }

    void disable()
    {
        setEnabled(false);
    }

    bool isEnabled() const
    {
        return connSource && connSource->isListenerEnabled(eventType, eventId);
    }

    bool connected() const
    {
        return connSource != nullptr;
    }

private:
    void setEnabled(bool enabled)
    {
        if (!connSource)
            return;

        connSource->setListenerEnabled(eventType, eventId, enabled);
    }

    void moveFrom(EventConnection &other)
    {
        connSource = other.connSource;
        prev = other.prev;
        next = other.next;
        eventType = other.eventType;
        eventId = other.eventId;

        if (prev)
            prev->next = this;
        else if (connSource)
            connSource->head = this;
        if (next)
            next->prev = this;

        // make the other invalid
        other.invalidate();
    }

    void invalidate()
    {
        connSource = nullptr;
        prev = nullptr;
        next = nullptr;
        eventType = EventRegistry::getTypeId<void>();
        eventId = 0;
    }

    ConnectionSource *connSource{};
    EventConnection *prev{};
    EventConnection *next{};
    EventTypeId eventType{EventRegistry::getTypeId<void>()};
    uint32_t eventId{};
};

inline ConnectionSource::~ConnectionSource()
{
    EventConnection *curConnection = head;
    while (curConnection)
    {
        EventConnection *next = curConnection->next;
        curConnection->connSource = nullptr;
        curConnection->prev = nullptr;
        curConnection->next = nullptr;
        curConnection = next;
    }
}

inline void ConnectionSource::registerConnection(EventConnection *connection)
{
    connection->next = head;
    connection->prev = nullptr;
    if (head)
        head->prev = connection;
    head = connection;
}

inline void ConnectionSource::unregisterConnection(EventConnection *connection)
{
    if (connection->prev)
        connection->prev->next = connection->next;
    else
        head = connection->next;
    if (connection->next)
        connection->next->prev = connection->prev;
    connection->prev = connection->next = nullptr;
}
