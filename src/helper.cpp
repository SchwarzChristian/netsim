#include "helper.hpp"

int tileset_len = 2;
Color * tileset[] = {
  new Color(  0, 255, 0, 255),
  new Color(127,   0, 0, 255)
};

Color::Color(color_t r, color_t g, color_t b, color_t a) {
  set(r, g, b, a);
}

Color& Color::set(color_t r, color_t g, color_t b, color_t a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
  return *this;
}

Color& Color::use() {
  glColor4i(r, g, b, a);
  return *this;
}

Color& Color::operator +=(Color other) {
  if (r + other.r < 0x100) r += other.r; else r = 0xff;
  if (g + other.g < 0x100) g += other.g; else g = 0xff;
  if (b + other.b < 0x100) b += other.b; else b = 0xff;
  if (a + other.a < 0x100) a += other.a; else a = 0xff;
  return *this;
}

Color& Color::operator +=(color_t other) {
  if (a + other < 0x100) a += other; else a = 0xff;
  return *this;
}

Color& Color::operator -=(Color other) {
  if (r - other.r > 0) r -= other.r; else r = 0;
  if (g - other.g > 0) g -= other.g; else g = 0;
  if (b - other.b > 0) b -= other.b; else b = 0;
  if (a - other.a > 0) a -= other.a; else a = 0;
  return *this;
}

Color& Color::operator -=(color_t other) {
  if (a - other > 0) a -= other; else a = 0;
  return *this;
}

void draw(terrain_t tile, int x, int y) {
  if (tile < tileset_len) tileset[tile]->use();
  glBegin(GL_QUADS);
  glVertex2i(x    , y    );
  glVertex2i(x + 1, y    );
  glVertex2i(x + 1, y + 1);
  glVertex2i(x    , y + 1);
  glEnd();
}
