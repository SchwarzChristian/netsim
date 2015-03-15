#include <cstdio>

#include "helper.hpp"

int get_random(int max){
  return rand() % max;
}
Point::Point(int x,int y){
  set(x,y);
}
Point& Point::set(int x, int y){
  this->x=x;
  this->y=y;
  return *this;
}
Point& Point::operator +(Point p){
  Point f(p);
  return f+=*this;
}
Point& Point::operator +=(Point p){
  x+=p.x;
  y+=p.y;
  return *this;
}

char* Point::to_s() {
  const int bufsize = 64;
  static char ret[bufsize];
  snprintf(ret, bufsize, "(%d;%d)", x, y);
  return ret;
}

Point::~Point(){
  
}

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
  glColor4ub(r, g, b, a);
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
