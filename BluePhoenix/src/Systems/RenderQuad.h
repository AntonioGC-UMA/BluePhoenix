#pragma once

#include "../Core/ECS.hpp"
#include "../Components/Transform.h"

class RenderQuad : public  ecs::BaseSystem<Transform>
{
public:
	RenderQuad();

	void Tick() final;

	~RenderQuad();

private:
	unsigned int shader;
	unsigned int VBO, VAO, EBO;
	unsigned int texture1, texture2;
};

