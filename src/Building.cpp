#include "Building.hpp"

Building::Building(string name, int maxhp, int price, int time) {
  _name         = name;
  _maxhp        = _hp = maxhp;
  _price        = price;
  _buildingtime = time;
}
