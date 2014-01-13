#include "../rogue.hpp"
#include "wall.hpp"

namespace rogue {
  Wall::Wall (Map& map, int x, int y, Direction dir):
    Object(map, x,y,Object::tWall,"Wall") {
    this->dir = dir;
  }
  
  Symbol Wall::symbol () {
    if (dir == Vertical)
      return Symbol(White,"ǁ");
    else
      return Symbol(White,"=");
  }

  State Wall::state () {
    return Solid;
  }
}
