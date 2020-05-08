
#include <iostream>
#include <chrono>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/Scene.h"


#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Components/Bounds.h"


#include "Systems/RenderTriangle.h"
#include "Systems/Mover.h"


using namespace std::chrono;
using namespace BP_ECS;

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


    Scene* scene = new Scene();

    unsigned trianguloX = scene->createEntity();
    unsigned trianguloY = scene->createEntity();

   
    /*      BUG : El renderer coje a la entidad dos veces porque al añadir un nuevo componente tengo que comprobar si el sistema ya 
            está afectando a esa entidad, y solo añadirla a la lista si no está ya

            solucionar en Scene.h AddComponent    
    */


    scene->addComponent<Velocity>(trianguloX, 0.0001, 0);
    scene->addComponent<Bounds>(trianguloX, 1, -1);
    scene->addComponent<Velocity>(trianguloY, 0, 0.0001);
    scene->addComponent<Bounds>(trianguloY, 1, -1);    

    System* mv = new Mover();
    scene->addSystem(mv);

    System* rt = new RenderTriangle();
    scene->addSystem(rt);
    
    scene->addComponent<Transform>(trianguloX);
    scene->addComponent<Transform>(trianguloY);




    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        /* Dibujar aqui !!!!1*/

        scene->Tick();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}