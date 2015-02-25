#include "helper.hpp"
#include <cstdio>

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
Point::~Point(){
}
