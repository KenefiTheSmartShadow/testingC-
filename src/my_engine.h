#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>

#include "primatives.h"

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
    _paddle = Rectangle(0.1, 0.42, 0.02, glm::vec3(-0.43, 0, 0),
                        glm::vec3(0, 0.02, 0));
    _paddle.createShader("../resources/shaders/paddle.vert",
                         "../resources/shaders/paddle.frag");

    _ball = Circle(glm::vec3(0), glm::vec3(0.02, 0.023, 0), 0.03);
    _ball.createShader("../resources/shaders/ball.vert",
                       "../resources/shaders/ball.frag");

    glDisable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(_window)) {
      glfwGetWindowSize(_window, &_width, &_height);

      processInput(_window);
      glClear(GL_COLOR_BUFFER_BIT);

      _paddle.draw();
      _ball.draw(glm::vec2(_width, _height));

      // Swap buffers and poll events
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }
    glfwDestroyWindow(_window);
    glfwTerminate();
  }

private:
  Rectangle _paddle;
  Circle _ball;
  GLFWwindow *_window;
  int _width = 800, _height = 600;

  void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      _paddle.move(1);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      _paddle.move(2);
  }
  static void error_callback(int error, const char *desc) {
    fprintf(stderr, "Error: %s\n", desc);
  }

  static void framebuffer_size_callback(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
  }
};
