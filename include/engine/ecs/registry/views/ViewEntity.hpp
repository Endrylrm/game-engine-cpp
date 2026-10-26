#pragma once

#include "ViewEntityIterator.hpp"

template <typename... Components>
class View;

template <typename... Components>
class ViewEntity
{
public:
    explicit ViewEntity(View<Components...> &view) : view(view) {}

    auto begin()
    {
        return view.begin_entity();
    }

    auto end()
    {
        return view.end_entity();
    }

private:
    View<Components...> &view;
};