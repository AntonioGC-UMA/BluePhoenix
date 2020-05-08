#pragma once

#include "../Core/System.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/Bounds.h"

struct Mover : public BP_ECS::BaseSystem<Transform, Velocity, Bounds>
{
	void Tick() override
	{
		for (auto& item : comp)
		{
			auto [trans, vel, bound] = item;

			trans->x += vel->x;
			trans->y += vel->y;

			if (trans->x > bound->right)
			{
				trans->x = bound->left;
			}
			if (trans->y > bound->right)
			{
				trans->y = bound->left;
			}
		}
	}
};

