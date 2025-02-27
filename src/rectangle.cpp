#include "primatives.h"

//
//  Constructors
//
Rectangle::Rectangle() : _width{0}, _height{0}, Object() {}

Rectangle::Rectangle(float width, float height)
    : _width{width}, _height{height}, Object() {}

Rectangle::Rectangle(float width, float height, float speed)
    : _width{width}, _height{height}, Object() {}

Rectangle::Rectangle(float width, float height, float speed,
                     glm::vec3 startingPosition)
    : _width{width}, _height{height}, Object(startingPosition) {}

Rectangle::Rectangle(float width, float height, float speed,
                     glm::vec3 startingPosition, glm::vec3 startingVelocity)
    : _width{width}, _height{height},
      Object(startingPosition, startingVelocity) {}

Rectangle::~Rectangle() { glDeleteProgram(_shader.ID); }

//
//  Private Functions
//

//
//  Public Functions
//
void Rectangle::draw() {
  glBindVertexArray(VAO);

  _shader.use();
  _position.y = glm::clamp(_position.y, -1 + _halfH, 1 - _halfH);
  glm::mat4 mat = glm::translate(glm::mat4(1.0), _position);
  _shader.setMat4("transform", mat);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Rectangle::move(int UP, int RIGHT) {
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

void Rectangle::setWidth(float width) {
  _width = width ? width >= 0 : 0;
  _halfW = width / 2.f;
}
float Rectangle::getWidth() { return _width; }
float getWidth(Rectangle &rectangle) { return rectangle.getWidth(); }

void Rectangle::setHeight(float height) {
  _height = height ? height >= 0 : 0;
  _halfH = height / 2.f;
}
float Rectangle::getHeight() { return _height; }
float Rectangle::getHeight(Rectangle &rectangle) {
  return rectangle.getHeight();
}

void Rectangle::createShader(const char *vertexPath, const char *fragmentPath) {
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Unbind VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cout << "OpenGL Error: " << error << std::endl;
  }
}
//
//  Operateor Overloads
//
std::ostream &operator<<(std::ostream &os, const Rectangle &rect) {
  os << rect._position.x << ", " << rect._position.y << "\n"
     << rect._velocity.x << ", " << rect._velocity.y << "\n"
     << "Width: " << rect._width << "\n"
     << "Height: " << rect._height << "\n";
  return os;
}
