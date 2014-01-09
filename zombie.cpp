#include <iostream>
#include "rogue/rogue.hpp"
using namespace rogue;
using namespace std;

class Wall: public Object {
public:
  Wall (int x, int y):
    Object(x,y,tWall) {
  }
};

int main (void) {
  Map map = Map(8,8);
  
  map.draw();

  return 0;
}
