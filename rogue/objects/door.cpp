#include "../rogue.hpp"
#include "door.hpp"

namespace rogue {
  Door::Door (Map& map, int x, int y, Direction dir):
    Object(map, x,y,Object::tDoor,"Door") {
    this->dir = dir;
    this->open = false;
  }
  
  Symbol Door::symbol () {
    return open?Symbol(White,"-"):Symbol(White,"+");
  }

  State Door::state () {
    return open?Gas:Solid;
  }
}
