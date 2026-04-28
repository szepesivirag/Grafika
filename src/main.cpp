#include <GLFW/glfw3.h> 
#include <iostream>

#include "callbacks.h"
#include "init.h"
#include "model.h"



int main(int argc, char* argv[])
{

    // GLFW inicializálása
    if (!glfwInit()) {
        std::cerr << "Hiba: Nem sikerult a GLFW inicializalasa!" << std::endl;
        return -1;
    }

    // Ablak létrehozása 
    GLFWwindow* window = glfwCreateWindow(1000, 700, "Szamitogepi Grafika Beadando", NULL, NULL);
    if (!window) {
        std::cerr << "Hiba" << std::endl;
        glfwTerminate();
        return -1;
    }

    // aktiv OpenGL ablak
    glfwMakeContextCurrent(window);

    World world;

    glfwSetWindowUserPointer(window, &world);

    init(&world);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // glutMainLoop() helyett ez lenne az uj megoldas
    while (!glfwWindowShouldClose(window))
    {
        
        display(window); 

        
        glfwSwapBuffers(window);
        
        // input feldolgozása
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}