#include "game/components/common/Faction.hpp"

FactionType Faction::getType() const
{
    return faction;
}

void Faction::setType(FactionType newFaction)
{
    faction = newFaction;
}