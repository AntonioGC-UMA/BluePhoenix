#pragma once

#include "../Core/System.h"
#include "../Components/Transform.h"

struct RenderTriangle : public  BP_ECS::BaseSystem<Transform>
{
	void Tick() override;
};
