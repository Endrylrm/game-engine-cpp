#pragma once
#include <cstdint>
#include <typeindex>

class ConnectionSource
{
    friend class EventConnection;

public:
    virtual ~ConnectionSource();

protected:
    virtual void disconnect(std::type_index type, uint32_t id) = 0;
    virtual void setListenerEnabled(std::type_index type, uint32_t id, bool enabled) = 0;
    virtual bool isListenerEnabled(std::type_index type, uint32_t id) = 0;

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
    EventConnection(ConnectionSource *source, std::type_index type, uint32_t id)
        : connSource(source), eventType(type), eventId(id)
    {
        source->registerConnection(this);
    }

    // delete copy
    EventConnection(const EventConnection &) = delete;
    EventConnection &operator=(const EventConnection &) = delete;

    // accepts move semantics
    EventConnection(EventConnection &&other) noexcept
    {
        moveFrom(other);
    }

    EventConnection &operator=(EventConnection &&other) noexcept
    {
        if (this != &other)
        {
            // clean current connection
            disconnect();
            moveFrom(other);
        }
        return *this;
    }

    ~EventConnection()
    {
        disconnect();
    }

    void disconnect()
    {
        if (!connSource)
            return;

        connSource->disconnect(eventType, eventId);
        connSource->unregisterConnection(this);
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
        eventType = typeid(void);
        eventId = 0;
    }

    ConnectionSource *connSource = nullptr;
    EventConnection *prev = nullptr;
    EventConnection *next = nullptr;
    std::type_index eventType = typeid(void);
    uint32_t eventId = 0;
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
