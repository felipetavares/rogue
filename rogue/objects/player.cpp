#include "../rogue.hpp"
#include "player.hpp"
#include <algorithm>

namespace rogue {
  Player::Player (Map& map, int x, int y):
    Object(map, x,y,Object::tPlayer,"Player") {
  }
  
  void Player::move (Map& map, int dx, int dy) {
    if (map.inside(dx,dy)) {
      if (std::all_of(map.data[dy][dx].begin(), map.data[dy][dx].end(),
		       [=] (Object *o) {return o->state() != Solid;}))
	Object::move (map, dx, dy);
    }
  }

  Symbol Player::symbol () {
    return Symbol(Green,"@");
  }

  State Player::state () {
    return Solid;
  }
}
