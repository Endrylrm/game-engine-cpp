#pragma once
#include <string>
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/Transform2D.hpp"
#include "engine/core/events/Connections.hpp"

class PlayerController : public Component
{
public:
	~PlayerController() override = default;
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDestruction() override;
	void print();

private:
	Transform2D *transform{};
	float speed{300.0f};
	EventConnection healthConnection;
};
