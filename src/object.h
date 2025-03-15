#include <glm/glm.hpp>
#include <ostream>

#include "shader.h"

class Object {
private:
protected:
  Shader _shader;

public:
  glm::vec3 _position;
  glm::vec3 _velocity;
  float vertices[0];
  unsigned int indices[0];
  Object() : _position{glm::vec3(0)}, _velocity{glm::vec3(0)} {}

  Object(glm::vec3 startingPosition)
      : _position{startingPosition}, _velocity{glm::vec3(0)} {}

  Object(glm::vec3 startingPosition, glm::vec3 startingVelocity)
      : _position{startingPosition}, _velocity{startingVelocity} {}

  virtual ~Object() {}

  friend std::ostream &operator<<(std::ostream &os, const Object &obj) {
    os << obj._position.x << ", " << obj._position.y << "\n"
       << obj._velocity.x << ", " << obj._velocity.y << "\n";
    return os;
  }

  void setPosition(glm::vec3 newPos) { _position = newPos; }
  glm::vec3 getPosition() { return _position; }
  static glm::vec3 getPosition(Object &object) { return object._position; }

  void setVelocity(glm::vec3 newVel) { _velocity = newVel; }
  glm::vec3 getVelocity() { return _velocity; }
  static glm::vec3 getVelocity(Object &object) { return object._velocity; }

  void createShader(const char *vertexPath, const char *fragmentPath) {
    if (vertexPath != nullptr && fragmentPath != nullptr)
      _shader = Shader(vertexPath, fragmentPath);
  }
};
