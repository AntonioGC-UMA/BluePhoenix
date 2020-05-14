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

			trans->pos.x += vel->vel.x;
			trans->pos.y += vel->vel.y;

			if (trans->pos.x > bound->right)
			{
				trans->pos.x = bound->left;
			}
			if (trans->pos.y > bound->right)
			{
				trans->pos.y = bound->left;
			}
		}
	}
};

