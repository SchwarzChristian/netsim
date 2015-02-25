#ifndef __HELPER_HPP__
#define __HELPER_HPP__
#include <cstdlib>
#include <ctime>

int get_random( int max);

class Point {
public:
  int x;
  int y;
  Point(int x=0,int y=0);
  Point& set(int x,int y);
  Point& operator +(Point p);
  Point& operator +=(Point p);
  ~Point();
};

#endif
