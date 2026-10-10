#include <iostream>
//#include <SDL3/SDL.h>
#include <GL/glew.h>
//#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <array>

// Window dimension
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

// Vertex Shader
std::string vShader("                                           \n\
#version 330                                                    \n\
                                                                \n\
layout (location = 0) in vec3 pos;                              \n\
                                                                \n\
void main(){                                                    \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);   \n\
}");

static const std::string fShader("                              \n\
#version 330                                                    \n\
                                                                \n\
out vec4 color;                                                 \n\
                                                                \n\
void main(){                                                    \n\
    color = vec4(1.0 ,0.0 ,0.0 , 1.0);                          \n\
}");


void CreateTriangle() {
    std::vector<GLfloat> vertices{
        -1.f, -1.f, 0.f,
        0.f, 1.f, 0.f,
        1.f, -1.f, 0.f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void AddShader(GLuint theProg, const std::string& shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode.data();

    GLint codeLength[1];
    codeLength[0] = shaderCode.length();

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint res(0);
    std::array<GLchar, 1024> err{};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &res);
    if (!res) {
        glGetShaderInfoLog(theShader, err.size(), nullptr, err.data());
        std::cout << "Error compilin the " << shaderType << " shader: " << err.data() << "\n";
        return;
    }

    glAttachShader(theProg, theShader);
}

void CompileShaders() {
    shader = glCreateProgram();

    if (!shader) {
        std::cout << "Error creating shader program\n";
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint res(0);
    std::array<GLchar, 1024> err{};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &res);
    if (!res) {
        glGetProgramInfoLog(shader, err.size(), nullptr, err.data());
        std::cout << "Error linking program: " << err.data() << "\n";
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &res);
    if (!res) {
        glGetProgramInfoLog(shader, err.size(), nullptr, err.data());
        std::cout << "Error validating program: " << err.data() << "\n";
        return;
    }
}

int main() {
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

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW init failed\n";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -1;
    }

    /*int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cout << "GLAD init failed\n";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -1;
    }*/

    glViewport(0, 0, bufferWidth, bufferHeight);

    CreateTriangle();
    CompileShaders();

    while (!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(0);

        glUseProgram(0);
        glfwSwapBuffers(mainWindow);
    }

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}