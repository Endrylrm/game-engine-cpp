#pragma once
#include <iostream>
#include "engine/entities/components/Component.hpp"
#include "engine/core/events/Signal.hpp"

class Health : public Component
{
public:
	Health() = default;
	Health(int startHP) : hp(startHP) {}
	Health(int startHP, int newMaxHP) : hp(startHP), maxHP(newMaxHP) {}
	~Health() override = default;
	void onAwake() override;
	void onUpdate(float deltaTime) override;
	void takeDamage(int damage);
	int getCurrentHP();
	int getMaxHP();

	Signal<> onDead;
	Signal<int> onHealthChanged;

private:
	int hp{};
	int maxHP{};
	int minHP{};
};
