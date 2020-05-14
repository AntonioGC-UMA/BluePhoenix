#pragma once

#include "../Core/ECS.hpp"
#include "../Components/Velocity.h"
#include "../Components/PlayerTag.h"

#include "../../glm/vec3.hpp"


#include "GLFW/glfw3.h"

struct PlayerInput : public ecs::BaseSystem<Velocity>
{
	GLFWwindow* ventana;

	PlayerInput(GLFWwindow* window) : ventana(window) {}

	bool filtrar(Key k) override
	{
		Key myKey = getKey<Velocity, PlayerTag>();
		return (myKey & k) == myKey;
	}

	void Tick() override
	{
		glm::vec3 vel = { 0,0,0 };

		if (glfwGetKey(ventana, GLFW_KEY_W) == GLFW_PRESS)
		{
			vel = { 0, 1, 0 };
		}
		else if (glfwGetKey(ventana, GLFW_KEY_A) == GLFW_PRESS)
		{
			vel = { -1, 0, 0 };
		}
		else if (glfwGetKey(ventana, GLFW_KEY_S) == GLFW_PRESS)
		{
			vel = { 0, -1, 0 };
		}
		else if (glfwGetKey(ventana, GLFW_KEY_D) == GLFW_PRESS)
		{
			vel = { 1, 0, 0 };
		}

		vel *= 0.0005;

		for (auto [entity, components] : comp)
		{
			auto [velocity] = components;

			velocity->vel = vel;
		}
	}
};