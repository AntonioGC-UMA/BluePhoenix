#pragma once

#include "../Core/System.h"
#include "../Components/Transform.h"

class RenderQuad : public  BP_ECS::BaseSystem<Transform>
{

public:
	RenderQuad();

	void Tick() final;

private:
	unsigned int shader;
};

