#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"

// Vertex Shader Source Code
const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

// Fragment Shader Source Code
const char *fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// Callback to adjust viewport on window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  // Create OpenGL Window
  GLFWwindow *_window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
  if (!_window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(_window);
  glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
  glfwSetKeyCallback(_window, key_callback);

  // Load OpenGL functions using glad
  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return -1;
  }

  // Triangle Vertices
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // Bottom left
      0.5f,  -0.5f, 0.0f, // Bottom right
      0.0f,  0.5f,  0.0f  // Top
  };

  //
  //  SHADER
  //
  Shader paddleShader("../resources/shaders/paddle.vert",
                      "../resources/shaders/paddle.frag");

  // Create VAO and VBO
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Bind VAO
  glBindVertexArray(VAO);

  // Bind and set VBO data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Set vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Unbind VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Render Loop
  while (!glfwWindowShouldClose(_window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Use shader program and draw triangle
    glUseProgram(paddleShader.ID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Swap buffers and poll events
    glfwSwapBuffers(_window);
    glfwPollEvents();
  }

  // Cleanup
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(paddleShader.ID);
  glfwDestroyWindow(_window);
  glfwTerminate();

  return 0;
}
