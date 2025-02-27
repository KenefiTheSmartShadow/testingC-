#include "primatives.h"

//
//  Constructors
//
Circle::Circle() : Object() {}

Circle::Circle(glm::vec3 startingPosition) : Object(startingPosition) {}

Circle::Circle(glm::vec3 startingPosition, glm::vec3 staringVelocity)
    : Object(startingPosition, staringVelocity) {}

Circle::Circle(glm::vec3 startingPosition, glm::vec3 staringVelocity,
               float startingRadius)
    : Object(startingPosition, staringVelocity), _radius{startingRadius} {}

Circle::~Circle() { glDeleteProgram(_shader.ID); }

//
//  Private Functions
//

//
//  Public Functions
//

void Circle::move() {
  _position += _velocity;
  screenBoundryCheck();
}

void Circle::screenBoundryCheck() {
  if (_position.x + _radius >= 1 || _position.x - _radius <= -1)
    _velocity.x *= -1;
  if (_position.y + _radius >= 1 || _position.y - _radius <= -1)
    _velocity.y *= -1;
}

void Circle::createShader(const char *vertexPath, const char *fragmentPath) {
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

void Circle::draw(glm::vec2 resolution) {
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

void Circle::checkRectangleCollision(Rectangle &otherRectangle) {
  glm::vec3 rectPos = otherRectangle.getPosition();
  glm::vec2 rectSize =
      glm::vec2(otherRectangle.getWidth(), otherRectangle.getHeight());
  bool couldColide = false;
  // is the circle in the verticle bounds of the rectangle
  couldColide = ((_position.y >= rectPos.y - rectSize.y / 2) &&
                 (_position.y <= rectPos.y + rectSize.y / 2));

  // is x position to the left or the right of the circle
  if (_position.x > rectPos.x) // to the right
  {
    if (_position.x + _radius <= rectPos.x + rectSize.x / 2 && couldColide)
      _velocity.x *= -1;
  } else if (_position.x > rectPos.x) // to the left
  {
    if (_position.x + _radius >= rectPos.x + rectSize.x / 2 && couldColide)
      _velocity.x *= -1;
  }
}

void Circle::checkCircleCollision(Circle otherCircle) {
  // TODO Check velocity vectors and change based off where the circles
  // collided with one another
}

//
//  Operator Overloads
//

ostream &operator<<(ostream &os, const Circle &circ) {
  os << circ._position.x << ", " << circ._position.y << "\n"
     << circ._velocity.x << ", " << circ._velocity.y << "\n"
     << "Radius: " << circ._radius << "\n";
  return os;
}
