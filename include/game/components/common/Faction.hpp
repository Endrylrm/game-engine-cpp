#pragma once
#include "engine/entities/components/Component.hpp"

enum class FactionType
{
    Neutral,
    Player,
    Enemy,
    Ally
};

class Faction : public Component
{
public:
    explicit Faction(FactionType faction) : faction(faction) {}

    FactionType getType() const;
    void setType(FactionType newFaction);

private:
    FactionType faction;
};