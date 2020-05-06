#pragma once

#include "../Core/System.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"

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

