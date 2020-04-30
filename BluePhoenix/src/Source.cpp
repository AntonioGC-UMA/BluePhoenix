
#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Entity.h"
#include "Transform.h"
#include "Physics.h"
#include "Renderer.h"

#include <chrono>

using namespace std::chrono;

int main(void)
{
    GLFWwindow* window;

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


    // Entidades y componentes;

    shared_ptr<Entity> triangulo = make_shared<Entity>();

    triangulo->addNewComponent<Transform>();
    triangulo->addNewComponent<Renderer>();
    triangulo->addNewComponent<Physics>()->vel = 0.001;


    shared_ptr<Entity> trianguloVeloz = make_shared<Entity>();

    trianguloVeloz->addNewComponent<Transform>();
    trianguloVeloz->addNewComponent<Renderer>();
    trianguloVeloz->addNewComponent<Physics>()->vel = 0.002;

    triangulo->addChild(trianguloVeloz);

    triangulo->start();

    auto lastFrame = system_clock::now();

    int frame = 0;

    float acumulatedDT = 0;

    float dt = 0;

    while (!glfwWindowShouldClose(window))
    {
        auto thisFrame = system_clock::now();
        duration<float, milli> duracion = thisFrame - lastFrame;
        dt = duracion.count();
        acumulatedDT += dt;
        lastFrame = thisFrame;
        
        frame++;

        if (acumulatedDT > 1000)
        {
            cout << "Frame time: " << frame / acumulatedDT << "\tFPS: " << frame << endl;
            acumulatedDT -= 1000;
            frame = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT);


        triangulo->update(dt);
        triangulo->lateUpdate();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}