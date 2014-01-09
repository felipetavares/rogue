#include <iostream>
#include "rogue/rogue.hpp"
using namespace rogue;
using namespace std;

int main (void) {
  Map map = Map(8,8);
  
  map.draw();

  return 0;
}
