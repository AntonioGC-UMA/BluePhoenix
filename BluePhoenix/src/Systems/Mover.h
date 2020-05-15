#pragma once

#include "../Core/ECS.hpp"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/Bounds.h"

struct Mover : public ecs::BaseSystem<Transform, Velocity, Bounds>
{
	void Tick(float dt) final
	{
		for (auto [entity, components] : comp)
		{
			auto [trans, vel, bound] = components;

			trans->pos += vel->vel * dt;

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

