#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "primatives.h"

class AIPlayer : public Rectangle {
public:
  AIPlayer() : Rectangle() {}
  AIPlayer(float width, float height) : Rectangle(width, height) {}
  AIPlayer(float width, float height, float speed)
      : Rectangle(width, height, speed) {}
  AIPlayer(float width, float height, float speed, glm::vec3 startingPosition)
      : Rectangle(width, height, speed, startingPosition) {}
  AIPlayer(float width, float height, float speed, glm::vec3 startingPosition,
           glm::vec3 startingVeloctiy)
      : Rectangle(width, height, speed, startingPosition, startingVeloctiy) {}

  void move(glm::vec3 otherPosition) {
    if (_position.y < otherPosition.y) // move up
      Rectangle::move(1, 0);
    else if (_position.y > otherPosition.y) // move up
      Rectangle::move(2, 0);
  }

private:
};
