#include <freetype/include/ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "shader.h"

class textRenderer {
public:
  textRenderer(const char *path_to_font) { initTextRenderer(path_to_font); }
  textRenderer(const char *path_to_font, unsigned int size) : _fontSize(size) {
    initTextRenderer(path_to_font);
  }

  ~textRenderer() {
    FT_Done_Face(_face);
    FT_Done_FreeType(_ft);
  }

  void renderText(const char *text, glm::vec3 position, glm::vec3 rotation);
  void renderText(const char *text, glm::vec3 position, glm::vec3 rotation,
                  float scale, glm::vec3 color);

private:
  static Shader _fontShader;
  FT_Library _ft;
  FT_Face _face;
  FT_CharMap _charmap;
  unsigned int _fontSize = 12;
  unsigned int VAO;

  void initTextRenderer(const char *path_to_font) {
    // text to render
    if (FT_Init_FreeType(&_ft)) {
      std::cerr << "Failed to initialize FreeType\n";
    }

    // font family
    if (FT_New_Face(_ft, path_to_font, 0, &_face)) {
      std::cerr << "Failed to load font\n";
    }

    // font size
    FT_Set_Pixel_Sizes(_face, 0, _fontSize);
  }

  void loadFont(const char *font_path);
};
