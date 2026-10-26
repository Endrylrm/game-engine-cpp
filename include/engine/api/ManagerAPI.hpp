#pragma once

class Engine;

template <typename Manager>
class ManagerAPI
{
    friend class Engine;

protected:
    static Manager &get_manager()
    {
        return *manager;
    }

private:
    static void set_manager(Manager *new_manager)
    {
        manager = new_manager;
    }

    static inline Manager *manager = nullptr;
};
