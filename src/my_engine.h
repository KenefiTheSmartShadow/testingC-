#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>

#include "game_objects.h"


class My_Engine {
public:
  My_Engine() {
    glfwSetErrorCallback(error_callback);
    glfwInit();

    _window = glfwCreateWindow(_width, _height, "Pong", nullptr, nullptr);
    if (!_window)
      cerr << "Failed to initialize window\n";
    
    glfwMakeContextCurrent(_window);

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD\n";
    }
  }

  void run() {
    Shader paddleShader("../resources/shaders/paddle.vert", "../resources/shaders/paddle.frag");
    unsigned int paddleVAO, paddleVBO, paddleEBO;
    glGenVertexArrays(1, &paddleVAO);
    glGenBuffers(1, &paddleVBO);
    glGenBuffers(1, &paddleEBO);

    // Bind VAO
    glBindVertexArray(paddleVAO);

    // Bind and set VBO data
    glBindBuffer(GL_ARRAY_BUFFER, paddleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_paddle.verts), _paddle.verts, GL_STATIC_DRAW);

    // Bind and set EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, paddleEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_paddle.indices), _paddle.indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cout << "OpenGL Error: " << error << std::endl;
    }
    Shader ballShader("../resources/shaders/ball.vert", "../resources/shaders/ball.frag");
    unsigned int ballVAO, ballVBO, ballEBO;
    glGenVertexArrays(1, &ballVAO);
    glGenBuffers(1, &ballVBO);
    glGenBuffers(1, &ballEBO);

    glBindVertexArray(ballVAO);

    // Bind and set VBO data
    glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_ball.verts), _ball.verts, GL_STATIC_DRAW);

    // Bind and set EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ballEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_ball.indices), _ball.indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cout << "OpenGL Error: " << error << std::endl;
    }
    glDisable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(_window)) {
      glfwGetWindowSize(_window, &_width, &_height);

      processInput(_window);
      glClear(GL_COLOR_BUFFER_BIT);
      
      glBindVertexArray(paddleVAO);
      _paddle.draw(paddleShader);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

      glBindVertexArray(ballVAO);
      _ball.draw(ballShader, glm::vec2(_width, _height));
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);


      // Swap buffers and poll events
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }
    glDeleteVertexArrays(0, &paddleVAO);
    glDeleteVertexArrays(0, &ballVAO);
    glDeleteBuffers(0, &paddleVBO);
    glDeleteBuffers(0, &paddleEBO);
    glDeleteBuffers(0, &ballVBO);
    glDeleteBuffers(0, &ballEBO);
    glDeleteProgram(paddleShader.ID);
    glDeleteProgram(ballShader.ID);
    glfwDestroyWindow(_window);
    glfwTerminate();
  }

private:
  Paddle _paddle;
  Ball _ball;
  GLFWwindow* _window;
  int _width=800, _height=600;

  void processInput(GLFWwindow *window)
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      _paddle.moveUp();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      _paddle.moveDown();
  }
  static void error_callback(int error, const char* desc) {
    fprintf(stderr, "Error: %s\n", desc);
  }

  static void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
  }
};
