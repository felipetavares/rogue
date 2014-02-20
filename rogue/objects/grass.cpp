#include "../rogue.hpp"
#include "grass.hpp"

namespace rogue {
  Grass::Grass (Map& map, int x, int y):
    Object(map, x,y,Object::tGrass,"Grass") {
  }

  Symbol Grass::symbol () {
    return Symbol(Green,Green," ");
  }

  State Grass::state () {
    return Gas;
  }

  float Grass::weight () {
    return 0.2;
  }
}