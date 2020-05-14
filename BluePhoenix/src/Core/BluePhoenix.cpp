#include "BluePhoenix.h"

#include <iostream>

#include "../Components/RotationSpeed.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/Bounds.h"
          

#include "../Systems/PlayerInput.h"
#include "../Systems/RenderQuad.h"
#include "../Systems/Rotate.h"
#include "../Systems/Mover.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int BluePhoenix::Init()
{
    if (!glfwInit())
    {
        std::cerr << "No se ha iniciado GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    scene.addComponent<Transform>(trianguloX, { {0,0,0}, 0 });    
    scene.addTag<PlayerTag>(trianguloX);

    scene.addComponent<Velocity>(trianguloY, { {0, 0.0005,0} });
    scene.addComponent<Bounds>(trianguloY, { 1.f, -1.f });
    scene.addComponent<Transform>(trianguloY, { {0,0,0}, 0 });
    scene.addComponent<RotationSpeed>(trianguloY, { 0.0001 });
}

void BluePhoenix::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scene.Tick();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void BluePhoenix::End()
{
    glfwTerminate();
}