#ifndef __MAPGEN_HPP__
#define __MAPGEN_HPP__

#include "helper.hpp"

typedef enum {TERRAIN_NORMAL,TERRAIN_TOWN} terrain_t;

class Map {
private:  
  terrain_t ** _map;
  int _w;
  int _h;
  Map& set(Point p,terrain_t type);
public:
  Map(int w, int h);
  Map();

  Map& init(int w, int h,int seed = time(NULL));
  Map& genTowns(int size,int count);
  Map& dump();

  ~Map();
};

#endif
