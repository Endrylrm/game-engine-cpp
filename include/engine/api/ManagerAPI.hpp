#pragma once

class Engine;

template <typename Manager>
class ManagerAPI
{
    friend class Engine;

protected:
    static Manager &getManager()
    {
        return *manager;
    }

private:
    static void setManager(Manager *newManager)
    {
        manager = newManager;
    }

    static inline Manager *manager = nullptr;
};