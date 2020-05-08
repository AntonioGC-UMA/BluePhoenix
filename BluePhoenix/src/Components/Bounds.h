#pragma once

#include "../Core/Component.h"

struct Bounds : public BP_ECS::Component
{
	Bounds(float r, float l) : right(r), left(l) {}

	float right = 1, left = -1;
};