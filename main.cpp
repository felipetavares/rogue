#include <iostream>
#include <algorithm>
#include <map>
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

void displayMessage(string);
char getDirection (int&, int&, bool=true);
int showOptionDialog (vector <pair<string,int>>);

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
  int i,j;
  int selected;
  vector < pair<string,int> > objectNameList;

  for (i=0;i<objs.size();i++)
    if (objs[i]->objectType() != Object::tPlayer)
      if (p->canPickup(objs[i]))
        objectNameList.push_back (pair<string,int>(objs[i]->getName(),i));

  if (objectNameList.size() == 1)
    selected = objectNameList[0].second;
  else  
    selected = showOptionDialog(objectNameList);

  if (selected != -1) {
    p->pickup(objs[selected]);
    objs.erase(objs.begin()+selected);
  }
}

template <class Dropper>
void drop (Map& map, Dropper *d) {
  auto elements = d->drop();

  for (auto *e :elements) {
    int dx,dy;
    getDirection(dx,dy,false);
    e->move(map, d->getX()+dx, d->getY()+dy, true);
  }
}

template <class Obj>
void action (Map& map, vector<Obj*> &objects, Object::Action action) {
  for (Obj* object :objects)
    object->action (map,action);
}

void display (Map& map, Player* player) {
    clearScreen();

    map.draw();
    
    player->displayCharacteristics();
    player->displayInventory();

    cout << "[MAP]" << endl;
    vector <Object*> &what = map.at(player);
    for_each (what.begin(),what.end(), [] (Object* o) {
      if (o->objectType() != Object::tPlayer) {
        o->completeDescription();
        cout << " ";
      }
    });
    cout << endl;
}

void displayMessage (string msg) {
  cout << msg;
  getc(stdin);
  cout << "\33[2K";
  cout << "\33[0G";
}

char getDirection (int &x, int &y, bool acceptAny) {
  x = y = 0;

  while (1) {
    if (acceptAny)
      cout << "[Command] ";
    else
      cout << "[Direction] ";

    char c = getc(stdin);

    if (c == 'j') {
      y = 1;
      break;
    }
    else
    if (c == 'k') {
      y = -1;
      break;
    }
    else
    if (c == 'h') {
      x = -1;
      break;
    }
    else
    if (c == 'l') {
      x = 1;
      break;
    }
    else
    if (c == 'b') {
      x = -1;
      y = 1;
      break;
    }
    else
    if (c == 'n') {
      x = 1;
      y = 1;
      break;
    }
    else
    if (c == 'y') {
      x = -1;
      y = -1;
      break;
    }
    else
    if (c == 'u') {
      x = 1;
      y = -1;
      break;
    }
    else
    if (c == ' ') {
      x = y = 0;
      break;
    }
    else
      if (acceptAny)
        return c;

    displayMessage ("Type a direction key!");
    cout << "\33[2K";
    cout << "\33[0G";
  }

  return 0;
}

int showOptionDialog (vector <pair <string,int>> options) {
  if (options.size() > 0) {
    int selected = 0;
    int dx,dy;
    char input = 0;

    while (1) {
      cout << "\33[1;1H\33[1K";

      for (int i=0;i<options.size();i++) {
        if (i == selected) {
          cout << "\33[7m" << options[i].first << "\33[0m ";
        } else
          cout << options[i].first << " ";
      }

      input = getDirection(dx,dy);

      selected += dx;

      if (selected < 0)
        selected = options.size()-1;
      else if (selected >= options.size())
        selected = 0;

      if (input == ',')
        break;
      if (input == 'q')
        return -1;
    }

    return options[selected].second;
  } else {
    return -1;
  }
}

int main (void) {
  Map map = Map("maps/tolkien/hobbit_home.rmp");
  Player *player = (Player*)map.getPlayer();

  Object *apple = new Apple(map, 5,5);
  Object *apple2 = new Apple(map, 5,5);

  cout << "\33\133\77" << "1049h";

  nonCanonicalStdin();
  while (player->alive()) {
    display(map, player);

    int dx,dy;

    char c = getDirection(dx,dy);

    if (c == 0)
      player->move(map, player->getX()+dx, player->getY()+dy);
    if (c == ',') {
        getDirection(dx,dy,false);
        pickup <Player,Object> (map, player, map.at(player->getX()+dx, player->getY()+dy));
    }

    if (c == 'e') {
      player->eat();
    }

    if (c == 'd')
        drop <Player> (map, player);

    if (c == 'o') {
        getDirection(dx,dy,false);
        action <Object> (map, map.at(player->getX()+dx, player->getY()+dy), Object::aOpen);
    }

    if (c == 'c') {
        getDirection(dx,dy,false);
        action <Object> (map, map.at(player->getX()+dx, player->getY()+dy), Object::aClose);
    }

    if (c == 'q')
      break;
  }

  displayMessage("You died...");

  restoreStdin();

  cout << "\33\133\77" << "1049l";

  cout << endl;

  return 0;
}
