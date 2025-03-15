#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <iostream>
#include <stdio.h>

#include "ai_player.h"

class My_Engine {
public:
  My_Engine() {
    glfwSetErrorCallback(error_callback);
    glfwInit();

    _window = glfwCreateWindow(_width, _height, "Pong", nullptr, nullptr);
    if (!_window)
      std::cerr << "Failed to initialize window\n";

    glfwMakeContextCurrent(_window);

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD\n";
    }

    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    ImGui::StyleColorsDark();

    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
  }

  void run() {
    _paddle = Rectangle(0.1, 0.42, 0.02, glm::vec3(-0.86, 0, 0),
                        glm::vec3(0, 0.02, 0));
    _paddle.createShader("../resources/shaders/paddle.vert",
                         "../resources/shaders/paddle.frag");

    _ball = Circle(glm::vec3(0), glm::vec3(-0.02, 0.023, 0), 0.03);
    _ball.createShader("../resources/shaders/ball.vert",
                       "../resources/shaders/ball.frag");

    _aiPlayer =
        AIPlayer(0.1, 0.42, 0.02, glm::vec3(0.86, 0, 0), glm::vec3(0, 0.02, 0));
    _aiPlayer.createShader("../resources/shaders/AIpaddle.vert",
                           "../resources/shaders/AIpaddle.frag");

    glfwSwapInterval(1);
    glDisable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(_window)) {

      glfwGetWindowSize(_window, &_width, &_height);

      processInput(_window);
      glClear(GL_COLOR_BUFFER_BIT);

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      ImGui::Begin("Options");

      ImGui::DragFloat3("Paddle 1 Pos", &_paddle._position.x);
      ImGui::DragFloat3("Paddle 2 Pos", &_aiPlayer._position.x);
      ImGui::DragFloat3("Ball Pos", &_ball._position.x);
      ImGui::Checkbox("Pause Rendering", &pauseRendering);

      ImGui::End();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwPollEvents();
      if (pauseRendering)
        continue;

      _ball.checkRectangleCollision(_paddle);
      _ball.checkRectangleCollision(_aiPlayer);

      _aiPlayer.draw();
      _aiPlayer.move(_ball.getPosition());

      _paddle.draw();
      /*cout << _paddle << "\n";*/
      _ball.draw(glm::vec2(_width, _height));
      /*cout << _ball << "\n";*/

      hasGoalHappened();

      // Swap buffers and poll events
      glfwSwapBuffers(_window);
    }
    glfwDestroyWindow(_window);
    glfwTerminate();
  }

private:
  Rectangle _paddle;
  Circle _ball;
  AIPlayer _aiPlayer;
  GLFWwindow *_window;
  int _width = 800, _height = 600;
  bool pauseRendering = false;

  void hasGoalHappened() {
    if (_ball.getPosition().x < _paddle.getPosition().x - _paddle.getWidth())
      _ball.setPosition(glm::vec3(0));
    else if (_ball.getPosition().x >
             _aiPlayer.getPosition().x + _aiPlayer.getWidth())
      _ball.setPosition(glm::vec3(0));
  }

  void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // pause rendering
      pauseRendering = true;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // resume rendering
      pauseRendering = false;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      _paddle.move(1);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      _paddle.move(2);
    // Ball debugging
    /*if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)*/
    /*  _ball.setPosition(_ball.getPosition() + glm::vec3(0, 0.002, 0));*/
    /*if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)*/
    /*  _ball.setPosition(_ball.getPosition() + glm::vec3(0, -0.002, 0));*/
    /*if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)*/
    /*  _ball.setPosition(_ball.getPosition() + glm::vec3(0.005, 0, 0));*/
    /*if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)*/
    /*  _ball.setPosition(_ball.getPosition() + glm::vec3(-0.005, 0, 0));*/
  }
  static void error_callback(int error, const char *desc) {
    fprintf(stderr, "Error: %s\n", desc);
  }

  static void framebuffer_size_callback(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
  }
};
