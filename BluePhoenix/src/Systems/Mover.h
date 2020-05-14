#pragma once

#include "../Core/ECS.hpp"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/Bounds.h"

struct Mover : public ecs::BaseSystem<Transform, Velocity, Bounds>
{
	void Tick() override
	{
		for (auto [entity, components] : comp)
		{
			auto [trans, vel, bound] = components;

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

