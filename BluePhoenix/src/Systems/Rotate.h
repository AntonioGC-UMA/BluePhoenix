#pragma once

#include "../Core/ECS.hpp"
#include "../Components/Transform.h"
#include "../Components/RotationSpeed.h"


struct Rotate : public ecs::BaseSystem<Transform, RotationSpeed>
{
	void Tick(float dt) override
	{
		for (auto [entity, components] : comp)
		{
			auto [tran, speed] = components;

			tran->rotation += speed->speed * dt;
		}
	}
};