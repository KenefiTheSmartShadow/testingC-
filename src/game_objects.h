#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

class Paddle {
private:
  glm::vec3 position = glm::vec3(-0.43, 0, 0);
  float width = 0.1, height = 0.42;
  float halfW = width/2.f, halfH = height/2.f;
  float speed = 0.02;
public:
  float verts[12] = {     
    halfW+position.x,  halfH+position.y, 0.0f,  // top right
    halfW+position.x, -halfH+position.y, 0.0f,  // bottom right
    -halfW+position.x, -halfH+position.y, 0.0f,  // bottom left
    -halfW+position.x,  halfH+position.y, 0.0f   // top left
  };
  unsigned int indices[6] = {
    0, 1, 3, 
    1, 2, 3
  };

  Paddle() {}

  void draw(Shader shader) {
    position.y = glm::clamp(position.y, -1 + halfH, 1 - halfH);
    shader.use();
    glm::mat4 mat = glm::translate(glm::mat4(1.0), position);
    shader.setMat4("transform", mat);
  }

  void moveUp() {
    position.y += speed;
  }
  void moveDown() {
    position.y -= speed;
  }
};

class Ball {
private:
  glm::vec2 position = glm::vec2(0); // screen coords (-1, 1)
  glm::vec2 velocity = glm::vec2(0.02, 0.023);
  float radius = 0.03; // size in screen coords

public:
  float verts[12] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
  };
  unsigned int indices[6] = { 
    0, 1, 3, 
    1, 2, 3 
  };

  Ball() {}
  ~Ball() {}

  void move() {
    position += velocity;
    collision_check();
  }

  void collision_check() {
    if (position.x + radius >= 1 || position.x - radius <= -1)
      velocity.x *= -1;
    if (position.y + radius >= 1 || position.y - radius <= -1)
      velocity.y *= -1;
  }
  
  void draw(Shader shader, glm::vec2 resolution) {
    move();

    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(position.x, position.y, 0.0f));

    shader.use();
    shader.setFloat("uBallRadius", radius);
    shader.setVec2("uResolution", resolution);
    shader.setMat4("transform", mat);
  }
};
