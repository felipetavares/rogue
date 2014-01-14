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
		       [] (Object *o) {return o->state() != Solid;}))
        Object::move (map, dx, dy);
    }
  }

  Symbol Player::symbol () {
    return Symbol(Green,"@");
  }

  State Player::state () {
    return Solid;
  }

  void Player::pickup (Object* o) {
    inventory.push_back (o);
  }

  vector <Object*> Player::drop () {
      if (inventory.size() > 0) {
        auto ret = vector<Object*> (inventory.begin(),inventory.begin()+1);
        inventory.erase(inventory.begin(), inventory.begin()+1);
        return ret;
      }
      return vector <Object*>();
  }

  void Player::displayInventory () {
    cout << "[INVENTORY]" << endl;
    for_each (inventory.begin(), inventory.end(), [] (Object* o) {
      o->completeDescription();
    });
  }
}
