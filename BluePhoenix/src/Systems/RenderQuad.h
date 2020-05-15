#pragma once

#include "../Core/ECS.hpp"
#include "../Components/Transform.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../../glm/glm.hpp"

class RenderQuad : public  ecs::BaseSystem<Transform>
{
public:
	RenderQuad(GLFWwindow* window);

	void Tick(float dt) final;

	~RenderQuad();

private:
	unsigned int shader;
	unsigned int VBO, VAO, EBO;
	unsigned int texture1, texture2;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 640 / 2.0;
	float lastY = 480 / 2.0;

	GLFWwindow* window;
};

