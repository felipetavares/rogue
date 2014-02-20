#include "../rogue.hpp"
#include "wall.hpp"

namespace rogue {
  Wall::Wall (Map& map, int x, int y, char dir):
    Object(map, x,y,Object::tWall,"Wall") {
    if (dir == '|')
      this->dir = Vertical;
    else
      this->dir = Horizontal;
  }

  Symbol Wall::symbol () {
    if (dir == Vertical)
      return Symbol(White,"|");
    else
      return Symbol(White,"-");
  }

  State Wall::state () {
    return Solid;
  }

  float Wall::weight () {
    return 10e10;
  }
}
