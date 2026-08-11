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
        return view.beginEntity();
    }

    auto end()
    {
        return view.endEntity();
    }

private:
    View<Components...> &view;
};