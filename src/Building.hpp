#ifndef __BUILDING_HPP__
#define __BUILDING_HPP__

#include <string>

using namespace std;

class Building {
  string _name;
  int    _maxhp;
  int    _hp;
  int    _price;
  int    _buildingtime;
public:
  Building(string name = "", int maxhp = 100, int price = 100, int time = 0);
};

#endif

