#pragma once

#include "../Core/Component.h"


struct Transform : public BP_ECS::Component
{
	double x = 0, y = 0;
};

