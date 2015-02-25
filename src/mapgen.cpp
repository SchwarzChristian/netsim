#include "mapgen.hpp"
#include <iostream>

using namespace std;

Map& Map::set(Point p,terrain_t type){
  if ( p.x >= 0 and p.x < _w and p.y >= 0 and p.y < _h ) {
      _map [p.y][p.x] = type;
    }
    return *this;
    }


Map::Map(){
  _map=NULL;
}

Map::Map(int w, int h){
  init(w,h);
}

 Map& Map::init(int w, int h,int seed){
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
 Map& Map::genTowns(int size,int count){
  Point p,q;
  int s_t=0;  
  for(;count>0;count--){
    p.set(get_random(_w),get_random(_h));
    set(p,TERRAIN_TOWN);
    s_t=get_random(size);    
    for(int i=0;i<s_t;i++){
      q.set(get_random(3)-1,get_random(3)-1);
      p+=q;
      set(p,TERRAIN_TOWN);
    }
  }
  return *this;
}

Map& Map::dump() {
  for (int i = 0; i < _h; i++) {
    for (int j = 0; j < _w; j++)
      cout << _map[i][j];
    cout << endl;
  }
  return *this;
}

Map::~Map(){
  if (not _map) return ;
  for(int i;i<_h;i++){
    delete [] _map[i];
  }
  delete [] _map;
  return;
}
