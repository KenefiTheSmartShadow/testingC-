#include "text_renderer.h"
#include <glm/ext/matrix_transform.hpp>

void textRenderer::renderText(const char *text, glm::vec3 position,
                              glm::vec3 rotation) {
  for (const char *p = text; *p != '\0'; p++) {
    char c = *p;
  }
}
void textRenderer::renderText(const char *text, glm::vec3 position,
                              glm::vec3 rotation, float scale,
                              glm::vec3 color) {}

void textRenderer::loadFont(const char *font_path) {}
