#include "BluePhoenix.h"

#include <iostream>
#include <chrono>

using namespace chrono;

#include "../Components/RotationSpeed.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/Bounds.h"
          

#include "../Systems/PlayerInput.h"
#include "../Systems/RenderQuad.h"
#include "../Systems/Rotate.h"
#include "../Systems/Mover.h"

#include "../../glm/gtc/matrix_transform.hpp"



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int BluePhoenix::Init()
{
    int width = 640, height = 480;
    if (!glfwInit())
    {
        std::cerr << "No se ha iniciado GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cerr << "No se ha creado la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK)
    {
        std::cerr << "No se ha iniciado GLEW" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return 0;
}

void BluePhoenix::Setup()
{
    Entity trianguloX = scene.createEntity();
    Entity trianguloY = scene.createEntity();

    scene.addSystem(new Mover());
    scene.addSystem(new RenderQuad());
    scene.addSystem(new Rotate());
    scene.addSystem(new PlayerInput(window));


    scene.addComponent<Velocity>(trianguloX, { {0,0,0} });
    scene.addComponent<Bounds>(trianguloX, { 1.f, -1.f });
    scene.addComponent<Transform>(trianguloX, { {0,0,0}, {0,0,0} });
    scene.addTag<PlayerTag>(trianguloX);

    scene.addComponent<Velocity>(trianguloY, { {0, 1,0} });
    scene.addComponent<Bounds>(trianguloY, { 1.f, -1.f });
    scene.addComponent<Transform>(trianguloY, { {0,0,0},  {0,0,0} });
    scene.addComponent<RotationSpeed>(trianguloY, { { 120, 0, 50} });
}

void BluePhoenix::Run()
{
    auto lastFrame = high_resolution_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        auto thisFrame = high_resolution_clock::now();

        std::chrono::duration<double> elapsed_seconds = thisFrame - lastFrame;

        lastFrame = thisFrame;

        scene.Tick(elapsed_seconds.count());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void BluePhoenix::End()
{
    glfwTerminate();
}