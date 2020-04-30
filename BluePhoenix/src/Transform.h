#pragma once

#include "Component.h"


struct Transform : public BaseComponent<Transform>
{
	double x, y;
};

