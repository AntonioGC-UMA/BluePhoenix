#pragma once

#include "System.h"
#include "Transform.h"
#include "Velocity.h"

struct RenderTriangle : public  BP_ECS::BaseSystem<Transform>
{
	void Tick() override;
};
