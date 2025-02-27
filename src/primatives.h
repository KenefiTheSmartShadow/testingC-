#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object.h"
using namespace std;

class Rectangle : public Object {
protected:
  float _width, _height;
  float _halfW = _width / 2.f, _halfH = _height / 2.f;

private:
  // Shader stuff
  unsigned int VAO;

public:
  float vertices[12] = {
      _halfW,  _halfH,  0.0f, // top right
      _halfW,  -_halfH, 0.0f, // bottom right
      -_halfW, -_halfH, 0.0f, // bottom left
      -_halfW, _halfH,  0.0f  // top left
  };
  unsigned int indices[6] = {0, 1, 3, 1, 2, 3};

  Rectangle();

  Rectangle(float width, float height);

  Rectangle(float width, float height, float speed);

  Rectangle(float width, float height, float speed, glm::vec3 startingPosition);

  Rectangle(float width, float height, float speed, glm::vec3 startingPosition,
            glm::vec3 startingVelocity);

  ~Rectangle();

  friend std::ostream &operator<<(std::ostream &os, const Rectangle &rect);

  void createShader(const char *vertexPath, const char *fragmentPath);

  void draw();

  void move(int UP = 0, int RIGHT = 0);

  void setWidth(float width);
  float getWidth();
  static float getWidth(Rectangle &rectangle);

  void setHeight(float height);
  float getHeight();
  static float getHeight(Rectangle &rectangle);
}; // end Rectangle

class Circle : public Object {
protected:
  float _radius = 0.03; // size in screen coordinates

private:
  // Shader stuff
  unsigned int VAO;

public:
  float vertices[12] = {-0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f,
                        0.5f,  0.5f,  0.0f, -0.5f, 0.5f,  0.0f};
  unsigned int indices[6] = {0, 1, 3, 1, 2, 3};

  Circle();

  Circle(glm::vec3 startingPosition);

  Circle(glm::vec3 startingPosition, glm::vec3 staringVelocity);

  Circle(glm::vec3 startingPosition, glm::vec3 staringVelocity,
         float startingRadius);

  ~Circle();

  friend std::ostream &operator<<(std::ostream &os, const Circle &circ);

  void move();
  void screenBoundryCheck();

  void createShader(const char *vertexPath, const char *fragmentPath);

  void draw(glm::vec2 resolution);

  void checkRectangleCollision(Rectangle &otherRectangle);
  void checkCircleCollision(Circle otherCircle);
}; // end Circle
