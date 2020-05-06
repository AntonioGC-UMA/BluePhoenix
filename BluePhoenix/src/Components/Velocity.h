#pragma once

#include "../Core/Component.h"

struct Velocity : public BP_ECS::Component
{
	float x = 0, y = 0;
};