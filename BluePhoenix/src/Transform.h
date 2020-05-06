#pragma once

#include "Component.h"


struct Transform : public BaseComponent<Transform>
{
	double x = 0, y = 0;
};

