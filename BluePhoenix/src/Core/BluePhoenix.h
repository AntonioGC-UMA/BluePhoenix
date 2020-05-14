#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "ECS.hpp"

using namespace ecs;

class BluePhoenix
{

public:

	int Init();
	void Setup();
	void Run();
	void End();

	GLFWwindow* window;
	Scene scene;
};

