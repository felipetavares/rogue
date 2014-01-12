#include <iostream>
#include "rogue/rogue.hpp"
#include "rogue/objects/wall.hpp"
using namespace rogue;
using namespace std;

int main (void) {
  Map map = Map(8,8);
  
  map.draw();

  return 0;
}
