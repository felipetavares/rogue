#include "../rogue.hpp"
#include "door.hpp"

namespace rogue {
  Door::Door (Map& map, int x, int y, char dir):
    Object(map, x,y,Object::tDoor,"Door") {
    if (dir == '/')
      this->dir = Vertical;
    else
      this->dir = Horizontal;

    this->open = false;
  }
  
  Symbol Door::symbol () {
    if (dir == Horizontal)
      return open?Symbol(Yellow,"|"):Symbol(Yellow,"+");
    else
      return open?Symbol(Yellow,"-"):Symbol(Yellow,"+");
  }

  State Door::state () {
    return open?Gas:Solid;
  }

  bool Door::action (Map& map, Action action) {
    if (action == aOpen) {
      open = true;
      return true;
    } else
    if (action == aClose) {
      open = false;
      return true;
    }

    return false;
  }

  float Door::weight () {
    return 10e10;
  }
}
