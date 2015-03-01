#ifndef __HELPER_HPP__
#define __HELPER_HPP__

#include "main.hpp"

typedef unsigned char color_t;
typedef enum {TERRAIN_NORMAL, TERRAIN_TOWN} terrain_t;

class Color {
public:
  color_t r;
  color_t g;
  color_t b;
  color_t a;

  Color(color_t r = 0, color_t g = 0, color_t b = 0, color_t a = 255);
  Color& set(color_t r, color_t g, color_t b, color_t a);
  Color& use();

  Color& operator +=(Color other);
  Color& operator +=(color_t other);
  Color& operator -=(Color other);
  Color& operator -=(color_t other);
};

void draw(terrain_t tile, int x, int y);

#endif
