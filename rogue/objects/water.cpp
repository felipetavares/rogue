#include "../rogue.hpp"
#include "water.hpp"

namespace rogue {
  Water::Water (Map& map, int x, int y):
    Object(map, x,y,Object::tWater,"Water") {
  }

  Symbol Water::symbol () {
    return Symbol(Blue,Blue,"~");
  }

  State Water::state () {
    return Liquid;
  }

  float Water::weight () {
    return 200;
  }
}
