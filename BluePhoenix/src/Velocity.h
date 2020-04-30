#pragma once

#include "Component.h"

struct Velocity : public BaseComponent<Velocity>
{
	float x, y;
};