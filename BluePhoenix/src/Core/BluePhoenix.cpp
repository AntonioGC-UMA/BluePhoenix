#include "BluePhoenix.h"

#include <iostream>

#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/Bounds.h"
          

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
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return 0;
}

void BluePhoenix::Setup()
{
    trianguloX = scene.createEntity();
    trianguloY = scene.createEntity();

    scene.addSystem(new Mover());
    scene.addSystem(new RenderQuad());


    scene.addComponent<Velocity>(trianguloX, { 0.0001f, 0.f });
    scene.addComponent<Bounds>(trianguloX, { 1.f, -1.f });
    scene.addComponent<Transform>(trianguloX, {0, 0});

    scene.addComponent<Velocity>(trianguloY, { 0.f, 0.0001f });
    scene.addComponent<Bounds>(trianguloY, { 1.f, -1.f });
    scene.addComponent<Transform>(trianguloY, {0, 0});
}

void BluePhoenix::Run()
{
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Dibujar aqui !!!!*/
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
                scene.addComponent<Bounds>(trianguloX, { 1,-1 });
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