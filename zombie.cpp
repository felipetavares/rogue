#include <iostream>
#include <algorithm>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include "rogue/rogue.hpp"
#include "rogue/objects/wall.hpp"
#include "rogue/objects/player.hpp"
#include "rogue/objects/door.hpp"
#include "rogue/objects/apple.hpp"
using namespace rogue;
using namespace std;

struct termios prevAttr;

void nonCanonicalStdin () {
  struct termios serialAttr;
        
  bzero (&serialAttr, sizeof (struct termios));

  serialAttr.c_oflag |= OCRNL | ONLCR | ONLRET | ONOCR | OPOST;
  serialAttr.c_cc[VMIN]  = 1;
  serialAttr.c_cc[VTIME] = 0;

  tcgetattr (1, &prevAttr);
  tcsetattr (1,TCSANOW,&serialAttr);
}

void restoreStdin () {
  tcsetattr (1,TCSANOW,&prevAttr);
}

void clearScreen () {
    cout << "\33[0;0f";
    cout << "\33[2J";
}

template <class Pickuper, class Obj>
void pickup (Map& map, Pickuper *p, vector<Obj*> &objs) {
  int i;
  for (i=0;i<objs.size();i++) {
    Obj* o = objs[i];
    if (o->objectType() != Object::tPlayer) {
      objs.erase(objs.begin()+i);
      p->pickup(o);
      i--;
    }
  }
}

template <class Dropper>
void drop (Map& map, Dropper *d) {
  vector <Object*> &v = map.data[d->getY()][d->getX()];
  auto elements = d->drop();

  v.insert(v.end()-1, elements.begin(), elements.end());
}

int main (void) {
  Map map = Map(8,8);
  Player *player = new Player (map, 1,1);
  Object *door = new Door(map, 3,3, Door::Vertical);
  Object *apple = new Apple(map, 5,5);

  nonCanonicalStdin();
  while (1) {
    clearScreen();

    map.draw();
    
    cout << "[MAP]" << endl;
    vector <Object*> &what = map.at(player);
    for_each (what.begin(),what.end(), [] (Object* o) {
      if (o->objectType() != Object::tPlayer)
        o->completeDescription();
    });

    player->displayInventory();

    char c;
    cin >> c;
 
    if (c == 'j')
      player->move(map, player->getX(), player->getY()+1);
    if (c == 'k')
      player->move(map, player->getX(), player->getY()-1);
    if (c == 'h')
      player->move(map, player->getX()-1, player->getY());
    if (c == 'l')
      player->move(map, player->getX()+1, player->getY());
    if (c == 'p')
        pickup <Player,Object> (map, player, map.at(player));
    if (c == 'd')
        drop <Player> (map, player);

    if (c == 'q')
      break;
  }
  restoreStdin();

  return 0;
}
