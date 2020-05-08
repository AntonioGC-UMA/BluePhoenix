#pragma once

#include "../Core/Component.h"

struct Velocity : public BP_ECS::Component
{
	Velocity(float x, float y) : x(x), y(y) {}

	float x = 0, y = 0;
};