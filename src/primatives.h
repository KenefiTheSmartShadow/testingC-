#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object.h"

class Rectangle : public Object {
private:
  float _width, _height;
  float _halfW = _width / 2.f, _halfH = _height / 2.f;

  // Shader stuff
  unsigned int VAO;

public:
  float vertices[12] = {
      _halfW + _position.x,  _halfH + _position.y,  0.0f, // top right
      _halfW + _position.x,  -_halfH + _position.y, 0.0f, // bottom right
      -_halfW + _position.x, -_halfH + _position.y, 0.0f, // bottom left
      -_halfW + _position.x, _halfH + _position.y,  0.0f  // top left
  };
  unsigned int indices[6] = {0, 1, 3, 1, 2, 3};

  Rectangle() : _width{0}, _height{0}, Object() {}

  Rectangle(float width, float height)
      : _width{width}, _height{height}, Object() {}

  Rectangle(float width, float height, float speed)
      : _width{width}, _height{height}, Object() {}

  Rectangle(float width, float height, float speed, glm::vec3 startingPosition)
      : _width{width}, _height{height}, Object(startingPosition) {}

  Rectangle(float width, float height, float speed, glm::vec3 startingPosition,
            glm::vec3 startingVelocity)
      : _width{width}, _height{height},
        Object(startingPosition, startingVelocity) {}

  ~Rectangle() { glDeleteProgram(_shader.ID); }

  void createShader(const char *vertexPath, const char *fragmentPath) {
    Object::createShader(vertexPath, fragmentPath);
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and set VBO data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cout << "OpenGL Error: " << error << std::endl;
    }
  }

  void draw() {
    glBindVertexArray(VAO);

    _shader.use();
    _position.y = glm::clamp(_position.y, -1 + _halfH, 1 - _halfH);
    glm::mat4 mat = glm::translate(glm::mat4(1.0), _position);
    _shader.setMat4("transform", mat);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void move(int UP = 0, int RIGHT = 0) {
    /*
     * @parameters
     * int UP = 0
     * int RIGHT = 0
     *
     * @description
     * Moves up when UP is 1, down when 2
     * Moves right when RIGHT is 1, left when 2
     * */
    if (UP == 1)
      _position.y += _velocity.y;
    else if (UP == 2)
      _position.y -= _velocity.y;
    if (RIGHT == 1)
      _position.x += _velocity.x;
    else if (RIGHT == 2)
      _position.x -= _velocity.x;
  }

  void setWidth(float width) {
    _width = width ? width >= 0 : 0;
    _halfW = width / 2.f;
  }
  void setHeight(float height) {
    _height = height ? height >= 0 : 0;
    _halfH = height / 2.f;
  }
}; // end Rectangle
//
//
//
//
//
//
//
//
//
class Circle : public Object {
private:
  float _radius = 0.03; // size in screen coordinates

  // Shader stuff
  unsigned int VAO;

public:
  float vertices[12] = {-0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f,
                        0.5f,  0.5f,  0.0f, -0.5f, 0.5f,  0.0f};
  unsigned int indices[6] = {0, 1, 3, 1, 2, 3};

  Circle() : Object() {}

  Circle(glm::vec3 startingPosition) : Object(startingPosition) {}

  Circle(glm::vec3 startingPosition, glm::vec3 staringVelocity)
      : Object(startingPosition, staringVelocity) {}

  Circle(glm::vec3 startingPosition, glm::vec3 staringVelocity,
         float startingRadius)
      : Object(startingPosition, staringVelocity), _radius{startingRadius} {}

  ~Circle() { glDeleteProgram(_shader.ID); }

  void move() {
    _position += _velocity;
    collision_check();
  }

  void collision_check() {
    if (_position.x + _radius >= 1 || _position.x - _radius <= -1)
      _velocity.x *= -1;
    if (_position.y + _radius >= 1 || _position.y - _radius <= -1)
      _velocity.y *= -1;
  }

  void createShader(const char *vertexPath, const char *fragmentPath) {
    Object::createShader(vertexPath, fragmentPath);
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Bind and set VBO data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cout << "OpenGL Error: " << error << std::endl;
    }
  }

  void draw(glm::vec2 resolution) {
    glBindVertexArray(VAO);

    _shader.use();
    move();

    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(_position.x, _position.y, 0.0f));

    _shader.use();
    _shader.setFloat("uBallRadius", _radius);
    _shader.setVec2("uResolution", resolution);
    _shader.setMat4("transform", mat);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}; // end Circle
//
//
//
