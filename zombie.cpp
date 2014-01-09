#include <iostream>
#include "rogue/rogue.hpp"
using namespace rogue;
using namespace std;

class Wall: public Object {
public:
  Wall (int x, int y):
    Object(x,y) {
  }
};

int main (void) {
  Object* wall = new Wall(0,0);

  cout << typeid(wall).name() << endl;

  return 0;
}
