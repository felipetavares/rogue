#include "../rogue.hpp"
#include "player.hpp"
#include <algorithm>
#include <cmath>

namespace rogue {
  Player::Player (Map& map, int x, int y):
    Object(map, x,y,Object::tPlayer,"Player"),
    cWeight(80),
    cEnergy(800) {
  }
  
  void Player::move (Map& map, int dx, int dy, bool bottom) {
    if (map.inside(dx,dy)) {
      if (std::all_of(map.data[dy][dx].begin(), map.data[dy][dx].end(),
		       [] (Object *o) {return o->state() == Gas;})) {
        float kx = (Object::x-dx);
        float ky = (Object::y-dy);
        Object::move (map, dx, dy);
        cEnergy -= 0.1*sqrt(kx*kx+ky*ky)+
        inventoryWeight()/cWeight;
      }
    }
  }

  Symbol Player::symbol () {
    return Symbol(Black,White,"@");
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
      cout << " ";
    });

    cout << endl;
  }

  void Player::displayCharacteristics () {
    cout << "[CHARACTERISTICS]" << endl;
    cout << "Weight:   " << cWeight << "kg" << endl;
    cout << "Carrying: " << inventoryWeight() << "kg" << endl;
    cout << "Energy: " << cEnergy << "cal" << endl;
  }

  float Player::weight () {
    return cWeight+inventoryWeight();
  }

  bool Player::canPickup (Object* o) {
    // A player can carry half of its weigth
    if (o->weight()+inventoryWeight() < cWeight/2)
      return true;
    return false;
  }

  float Player::inventoryWeight () {
    float w = 0;

    for (auto o :inventory) {
      w += o->weight();
    }
    
    return w;
  }

  void Player::eat () {
    if (inventory.size() > 0) {
      if (inventory[0]->isComestible()) {
        cEnergy += inventory[0]->nutritionValue();
        inventory.erase(inventory.begin(),inventory.begin()+1);
      }
    }
  }

  bool Player::alive () {
    if (cEnergy > 0)
      return true;
    else
      return false;
  }
}
