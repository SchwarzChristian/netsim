#ifndef __MAPGEN_HPP__
#define __MAPGEN_HPP__

#include "helper.hpp"

#define PI 3.1415926535

typedef enum {
  TERRAIN_NORMAL,
  TERRAIN_TOWN,
  TERRAIN_MOUNTAIN,
  TERRAIN_LAKE,
  TERRAIN_RIVER
} terrain_t;

class Chunk {
private:
  terrain_t ** _map;
  int _dlist;
  int _w;
  int _h;
  
  terrain_t& operator[](Point& other);
public:
  Chunk(int w, int h);
  Chunk();

  Chunk& init(int w, int h,int seed = time(NULL));
  Chunk& genTowns(int size,int count);
  Chunk& genLakes(int size,int count);
  Chunk& genRivers(int size, int count, float variation);
  Chunk& genMountains(int size, int count);  
  Chunk& dump();
  Chunk& draw();

  ~Chunk();
};

#endif
