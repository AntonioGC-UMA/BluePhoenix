#pragma once

#include "../Core/Component.h"

struct Bounds : public BP_ECS::Component
{
	float right = 1, left = -1;
};