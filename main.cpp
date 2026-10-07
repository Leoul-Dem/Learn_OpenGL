#include <iostream>
//#include <SDL3/SDL.h>
// #include <GL/glew.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>


const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
    if (!glfwInit()) {
        std::cout << "GLFW init failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* mainWindow =
        glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);

    // Failure = nullptr
    if (!mainWindow) {
        std::cout << "GLFW window creation failed\n";
        glfwTerminate();
        return -1;
    }

    // OpenGL context must exist before initializing GLEW
    glfwMakeContextCurrent(mainWindow);

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // glewExperimental = GL_TRUE;

    // if (glewInit() != GLEW_OK) {
    //     std::cout << "GLEW init failed\n";
    //     glfwDestroyWindow(mainWindow);
    //     glfwTerminate();
    //     return -1;
    // }

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cout << "GLAD init failed\n";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, bufferWidth, bufferHeight);

    while (!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}