
#include <iostream>
#include <chrono>

#include "GL/glew.h"
#include "GLFW/glfw3.h"


#include "Scene.h"
#include "Transform.h"
#include "Velocity.h"
#include "Mover.h"
#include "RenderTriangle.h"

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


    Scene* scene = new Scene();

    unsigned triangulo = scene->CreateEntity();

    System* m = new Mover({ BaseComponent<Transform>::type, BaseComponent<Velocity>::type });
    System* t = new RenderTriangle({ BaseComponent<Transform>::type }); 

    /*
    
    BUG : El renderer coje a la entidad dos veces porque al añadir un nuevo componente tengo que comprobar si el sistema ya 
            está afectando a esa entidad, y solo añadirla a la lista si no está ya

            solucionar en Scene.h AddComponent
    
    */

    scene->AddSystem(m);
    scene->AddSystem(t);
    

    scene->AddComponent<Transform>(triangulo);
    scene->AddComponent<Velocity>(triangulo).lock()->x = 0.0001;



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

        /* Dibujar aqui !!!!1*/

        scene->Update();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}