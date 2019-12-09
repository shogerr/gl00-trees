#include <gl00/gl00.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "test_signal.hpp"
#include "cylinder_sketch.hpp"

static void error_callback(int error, const char* description)
{
    fprintf(stdout, "Error: %s\n", description);
}

int main()
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640,480,"Cylinder Test", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);

    gl00::Engine engine;
    //engine.SetDefaultScene(std::make_unique<gl00::scenes::TestSignal>());
    engine.SetDefaultScene(std::make_unique<CylinderSketch>());

    while (!glfwWindowShouldClose(window))
    {
        engine.DoFrame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
