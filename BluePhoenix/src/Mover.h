#pragma once

#include "System.h"
#include "Transform.h"
#include "Velocity.h"

struct Mover : public BP_ECS::BaseSystem<Transform, Velocity>
{
	void Tick() override
	{
		for (auto& item : comp)
		{
			auto [trans, vel] = item;

			trans->x += vel->x;
			trans->y += vel->y;
		}
	}
};

