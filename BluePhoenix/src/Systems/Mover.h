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

			trans->position += vel->vel * dt;

			if (trans->position.x > bound->right)
			{
				trans->position.x = bound->left;
			}
			if (trans->position.y > bound->right)
			{
				trans->position.y = bound->left;
			}
		}
	}
};

