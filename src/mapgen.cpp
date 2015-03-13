#include <iostream>

#include "mapgen.hpp"
#include "List.hpp"

using namespace std;

int tileset_len = 3;
Color *tileset[] = {
  new Color(  0, 255,   0, 255),	// TERRAIN_NORMAL
  new Color(127,   0,   0, 255),	// TERRAIN_TOWN
  new Color(127, 127, 127, 255)		// TERRAIN_MOUNTAIN
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
  Point p,q;
  int s_t=0;
  
  for(;count>0;count--){
    p.set(get_random(_w),get_random(_h));
    (*this)[p] = TERRAIN_MOUNTAIN;
    s_t=get_random(size);    
    for(int i=0;i<s_t;i++){
      q.set(get_random(3)-1,get_random(3)-1);
      p+=q;
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
