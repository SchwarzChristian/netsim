#include "mapgen.hpp"
int main(){
  Map la(100,40);
  la.genTowns(20,7).dump();
  return 0;
}
