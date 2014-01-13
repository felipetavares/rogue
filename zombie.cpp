#include <iostream>
#include <algorithm>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include "rogue/rogue.hpp"
#include "rogue/objects/wall.hpp"
#include "rogue/objects/player.hpp"
#include "rogue/objects/door.hpp"
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
    cout << "\33[2J";
}

int main (void) {
  Map map = Map(8,8);
  Player *player = new Player (map, 1,1);
  new Door(map, 3,3, Door::Vertical);

  nonCanonicalStdin();
  while (1) {
    clearScreen();

    map.draw();
    vector <Object*> what = map.at(player);
    for_each (what.begin(),what.end(), [] (Object* o) {
	o->completeDescription();
      });

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

    if (c == 'q')
      break;
  }
  restoreStdin();

  return 0;
}
