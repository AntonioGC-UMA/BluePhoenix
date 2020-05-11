#include "BluePhoenix.h"

#include <iostream>

#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/Bounds.h"
          
          
#include "../Systems/RenderTriangle.h"
#include "../Systems/RenderQuad.h"
#include "../Systems/Mover.h"

bool pulsado = false;

unsigned trianguloX;
unsigned trianguloY;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        pulsado = true;        
    }
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
    glfwSetKeyCallback(window, key_callback);

    return 0;
}

void BluePhoenix::Setup()
{
    trianguloX = scene.createEntity();
    trianguloY = scene.createEntity();

    scene.addSystem(new Mover());
    scene.addSystem(new RenderQuad());


    scene.addComponent<Velocity>(trianguloX, 0.0001f, 0.f);
    scene.addComponent<Bounds>(trianguloX, 1.f, -1.f);
    scene.addComponent<Transform>(trianguloX);

    scene.addComponent<Velocity>(trianguloY, 0.f, 0.0001f);
    scene.addComponent<Bounds>(trianguloY, 1.f, -1.f);
    scene.addComponent<Transform>(trianguloY);
}

void BluePhoenix::Run()
{
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Dibujar aqui !!!!1*/
        static bool estado = false;
        if (pulsado)
        {
            pulsado = false;
            if (!estado)
            {
                scene.removeComponent<Bounds>(trianguloX);
            }
            else
            {
                scene.addComponent<Bounds>(trianguloX, 1, -1);
            }
            estado = !estado;
        }


        scene.Tick();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void BluePhoenix::End()
{
    glfwTerminate();
}