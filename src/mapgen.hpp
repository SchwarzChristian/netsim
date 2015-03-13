#ifndef __MAPGEN_HPP__
#define __MAPGEN_HPP__

#include "helper.hpp"

typedef enum { TERRAIN_NORMAL, TERRAIN_TOWN, TERRAIN_MOUNTAIN } terrain_t;

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
  Chunk& genMountains(int size, int count);  
  Chunk& dump();
  Chunk& draw();

  ~Chunk();
};

#endif
