#include "../rogue.hpp"
#include "apple.hpp"

namespace rogue {
  Apple::Apple (Map& map, int x, int y):
    Object(map, x,y,Object::tApple,"Apple") {
  }
  
  Symbol Apple::symbol () {
    return Symbol(Red, "a");
  }

  State Apple::state () {
    return Gas;
  }
}
