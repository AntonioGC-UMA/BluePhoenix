#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Scene.h"

using namespace BP_ECS;


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

