#include <iostream>
#include <math.h>
#include <cstdio>

#include "mapgen.hpp"
#include "List.hpp"

using namespace std;

List<Point> rivCan;

int tileset_len = 5;
Color *tileset[] = {
  new Color(  0, 255,   0, 255),	// TERRAIN_NORMAL
  new Color(127,   0,   0, 255),	// TERRAIN_TOWN
  new Color(127, 127, 127, 255),	// TERRAIN_MOUNTAIN
  new Color( 63,  63, 255, 255),	// TERRAIN_LAKE
  new Color(  0,   0, 255, 255)		// TERRAIN_RIVER
};

terrain_t& Chunk::operator[](Point& other) {
  if (other.x < _w and other.x > 0 and other.y < _h and other.y > 0)
    return _map[other.y][other.x];
  else return _map[0][0];
}

Chunk::Chunk(){
  _map=NULL;
  _dlist = -1;
}

Chunk::Chunk(int w, int h){
  init(w,h);
}

Chunk& Chunk::init(int w, int h,int seed){
  _dlist = -1;
  _w=w;
  _h=h;
  srand(seed);
  _map = new terrain_t*[h];
  for(int i=0; i<h;i++){
    _map[i]= new terrain_t[w];
    for(int j=0;j<w;j++){
      _map[i][j]=TERRAIN_NORMAL;
    }
  }
  return *this;
}

Chunk& Chunk::genMountains(int size,int count){
  Point p;
  int s_t=0;
  List<Point> neighbors;
  
  for(;count>0;count--){
    do {
      p.set(get_random(_w),get_random(_h));
    } while ((*this)[p] != TERRAIN_NORMAL);
    (*this)[p] = TERRAIN_MOUNTAIN;
    s_t=get_random(size);    
    for(int i=0;i<s_t;i++){
      for (int i = -1; i <= 1; i++)
	for (int j = -1; j <= 1; j++)
	  if ((i or j) and this->_map[p.y + j][p.x + i] == TERRAIN_NORMAL)
	    neighbors += new Point(p.x + i, p.y + j);
      if (!neighbors.count()) continue;
      neighbors >> get_random(neighbors.count());
      p.set(*neighbors.current());
      (*this)[p] = TERRAIN_MOUNTAIN;
    }
  }
  return *this;
}

Chunk& Chunk::genTowns(int size, int count){
  Point p;
  int s_t=0;
  List<Point>* list;

  for(;count>0;count--) {
    p.set(get_random(_w),get_random(_h));
    s_t = get_random(size);
    list = new List<Point>();
    for(int i=0;i<s_t;i++) {
      if(i){
	while((*this)[p] != TERRAIN_NORMAL and list->count() ) {
	  p=*((*list)>>get_random(list->count())).current();
	  (*list)--;
	}
	if(not list->count()) break;
      }
      (*list)+=new Point(p.x+1,p.y);
      (*list)+=new Point(p.x  ,p.y+1);
      (*list)+=new Point(p.x-1,p.y);
      (*list)+=new Point(p.x  ,p.y-1);
      (*this)[p] = TERRAIN_TOWN;
    }
    delete list;
  }
  return *this;
}

Chunk& Chunk::genLakes(int size, int count) {
  Point p;
  int s_t=0;
  List<Point>* list;

  for(;count>0;count--) {
    p.set(get_random(_w),get_random(_h));
    s_t = get_random(size);
    list = new List<Point>();
    for(int i=0;i<s_t;i++) {
      if(i){
	while((*this)[p] != TERRAIN_NORMAL and list->count() ) {
	  p=*((*list)>>get_random(list->count())).current();
	  (*list)--;
	}
	if(not list->count()) break;
      }
      (*list)+=new Point(p.x+1,p.y);
      (*list)+=new Point(p.x  ,p.y+1);
      (*list)+=new Point(p.x-1,p.y);
      (*list)+=new Point(p.x  ,p.y-1);
      (*this)[p] = TERRAIN_LAKE;
      rivCan += new Point(p);
    }
    delete list;
  }  
  return *this;
}

Chunk& Chunk::genRivers(int size, int count, float variation) {
  Point start, target, *tmp, curr;
  float angle, directAngle;
  List<Point> path;

  while (count--) {
    tmp = &start;
  and_again:
    if (get_random(2)) {
      rivCan >> get_random(rivCan.count());
      tmp->set(*rivCan.current());
    } else {
      switch (get_random(4)) {
      case DIR_NORTH:
	tmp->set(get_random(_w), 0);
	break;
      case DIR_SOUTH:
	tmp->set(get_random(_w), _h);
	break;
      case DIR_EAST:
	tmp->set(0, get_random(_h));
	break;
      case DIR_WEST:
	tmp->set(_w, get_random(_h));
	break;
      }
    }
    if (tmp == &start) {
      tmp = &target;
      goto and_again;
    }

    curr.set(start);

    while (curr != target) {
      if (not(target.x - curr.x)) {
	directAngle = curr.y > target.y ? angle = 0 : PI;
      } else {
	directAngle = atan((target.y - curr.y) / (target.x - curr.x));
      }

      angle = directAngle + ((get_random(200) / 100.0 - 1) * variation);
      if (angle > directAngle and angle <  directAngle + variation / 4)
	angle += variation / 4;
      if (angle < directAngle and angle > directAngle - variation / 4)
	angle -= variation / 4;
    
      while (angle < 0) angle += 2 * PI;
      while (angle > 2 * PI) angle -= 2 * PI;

      if      (angle <      PI / 8) curr.mod( 0, -1);
      else if (angle < 3  * PI / 8) curr.mod( 1, -1);
      else if (angle < 5  * PI / 8) curr.mod( 1,  0);
      else if (angle < 7  * PI / 8) curr.mod( 1,  1);
      else if (angle < 9  * PI / 8) curr.mod( 0,  1);
      else if (angle < 11 * PI / 8) curr.mod(-1,  1);
      else if (angle < 13 * PI / 8) curr.mod(-1,  0);
      else if (angle < 15 * PI / 8) curr.mod(-1, -1);
      else			    curr.mod( 0, -1);

      path += new Point(curr);
      if ((*this)[curr] == TERRAIN_RIVER or
	  curr.x <= 0 or curr.x >= _w or
	  curr.y <= 0 or curr.y >= _h)
	break;
    }
    while (path.count()) {
      (*this)[*path.current()] = TERRAIN_RIVER;
      path--;
    }
  }
  return *this;
}


Chunk& Chunk::dump() {
  for (int i = 0; i < _h; i++) {
    for (int j = 0; j < _w; j++)
      cout << _map[i][j];
    cout << endl;
  }
  return *this;
}

Chunk& Chunk::draw() {
  if (_dlist < 0) {
    _dlist = glGenLists(1);
    glNewList(_dlist, GL_COMPILE);
    glBegin(GL_QUADS);
    for (int y = 0; y < _h; y++)
      for (int x = 0; x < _w; x++) {
	if (_map[y][x] < tileset_len) tileset[_map[y][x]]->use();
	else tileset[0]->use();
	glVertex2i(x    , -y    );
	glVertex2i(x    , -y - 1);
	glVertex2i(x + 1, -y - 1);
	glVertex2i(x + 1, -y    );
      }
    glEnd();
    glEndList();
  }
  glCallList(_dlist);
  return *this;
}

Chunk::~Chunk(){
  if (not _map) return ;
  for(int i;i<_h;i++){
    delete [] _map[i];
  }
  delete [] _map;
  return;
}
