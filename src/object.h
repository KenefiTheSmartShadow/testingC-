#include <glm/glm.hpp>

#include "shader.h"

class Object {
private:
protected:
  glm::vec3 _position;
  glm::vec3 _velocity;
  Shader _shader;

public:
  float vertices[0];
  unsigned int indices[0];
  Object() : _position{glm::vec3(0)}, _velocity{glm::vec3(0)} {}

  Object(glm::vec3 startingPosition)
      : _position{startingPosition}, _velocity{glm::vec3(0)} {}

  Object(glm::vec3 startingPosition, glm::vec3 startingVelocity)
      : _position{startingPosition}, _velocity{startingVelocity} {}

  virtual ~Object() {}

  void setPosition(glm::vec3 newPos) { _position = newPos; }
  void setVelocity(glm::vec3 newVel) { _velocity = newVel; }

  void createShader(const char *vertexPath, const char *fragmentPath) {
    if (vertexPath != nullptr && fragmentPath != nullptr)
      _shader = Shader(vertexPath, fragmentPath);
  }
};
