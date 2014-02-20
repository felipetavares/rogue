#include <algorithm>
#include <fstream>
#include "rogue.hpp"
#include "objects/wall.hpp"
#include "objects/door.hpp"
#include "objects/player.hpp"
#include "objects/grass.hpp"
#include "objects/water.hpp"
#include "properties/properties.hpp"

namespace rogue {
  // Init a symbol
  Symbol::Symbol () {
    foreground = White;
    background = Black;
    character = ' ';
  }
  
  Symbol::Symbol (Color foreground, string character) {
    this->foreground = foreground;
    this->background = Black;
    this->character = character;
  }
  
  Symbol::Symbol (Color foreground, Color background, string character) {
    this->foreground = foreground;
    this->background = background;
    this->character = character;
  }

  void Symbol::draw () {
    cout << "\33[3";
    cout << foreground;
    cout << "m";
    cout << "\33[4";
    cout << background;
    cout << "m";
    cout << character;
    cout << "\33[0m";
  }
  
  Object::Object (Map& map,int x, int y, Type type, string name) {
    this->type = type;
    this->name = name;
    move(map, x, y);
  }
  
  Object::Type Object::objectType () {
    return this->type;
  }

  string Object::getName () {
    return name;
  }

  void Object::move (Map& map, int dx, int dy, bool bottom) {
    if (map.inside (x,y)) {
      vector <Object*> &v = map.data[y][x];
      v.erase(remove(v.begin(), v.end(), this), v.end());
    }
    if (map.inside(dx,dy)) {
      if (bottom)
        map.data[dy][dx].insert(map.data[dy][dx].begin(), this);
      else
        map.data[dy][dx].push_back(this);
      x = dx;
      y = dy;
    }
  }

  void Object::completeDescription () {
    cout << name;
  }

  int Object::getX() {
    return x;
  }

  int Object::getY() {
    return y;
  }
  
  Map::Map (int w, int h, string name):
    data(NULL) {
    this->w = w;
    this->h = h;
    this->name = name;

    data = new vector <Object*>*[h];
    for (int i=0;i<h;i++) {
      data[i] = new vector <Object*>[w];
      for (int j=0;j<w;j++) {
      	bool hasdir = false;
      	Wall::Direction dir;
      	
      	if (i == 0 || i == h-1) {
      	  dir = Wall::Horizontal;
      	  hasdir = true;
      	}
      	else if (j == 0 || j == w-1) {
      	  dir = Wall::Vertical;
      	  hasdir = true;
      	}

      	if (hasdir)
      	  new Wall(*this,j,i,dir);
      }
    }
  }
  
  Map::~Map () {
    for (int i=0;i<h;i++)
      delete[] data[i];
    delete[] data;
  }
  
  void Map::draw () {
    cout << name << endl;

    int x,y;
    for (y=0;y<h;y++) {
      for (x=0;x<w;x++) {
      	if (data[y][x].size() > 0) {
      	  data[y][x].back()->symbol().draw();
      	} else {
      	  Symbol(White," ").draw();
      	} 
      }
      cout << endl;
    }
  }

  vector <Object*> &Map::at (Object *o) {
    if (inside (o->getX(), o->getY())) {
      return data[o->getY()][o->getX()];
    }

    return vnull;
  }

  vector <Object*> &Map::at (int x, int y) {
    if (inside (x,y)) {
      return data[y][x];
    }
    return vnull;
  }

  bool Map::inside (int x, int y) {
    if (x >= 0 && y >= 0 &&
	      x < w  && y < h)
      return true;
    return false;
  }

  Map::Map (string fname):
    data(NULL) {
    std::fstream file;
    file.open(fname.c_str(), ios::in);

    if (file.is_open()) {
      getline (file, name);
      cout << "Loading map '" << name << "'..." << endl;

      file >> w >> h;
      cout << "Size: (" << w << ", " << h << ")" << endl;

      data = new vector <Object*>*[h];
      for (int i=0;i<h;i++) {
        data[i] = new vector <Object*>[w];
        for (int j=0;j<w;j++) {
          char mapCharacter;
          file >> mapCharacter;

          switch (mapCharacter) {
            case 'x':
            break;
            case '@':
              player = new Player(*this,j,i);
            break;
            case '|':
            case '-':
              new Wall (*this, j, i, mapCharacter);
            break;
            case '/':
            case '=':
              new Door (*this, j, i, mapCharacter);
            break;
            case '#':
              new Grass (*this, j, i);
            break;
            case '~':
              new Water (*this, j, i);
            break;
          }
        }
      }      
    } else {
      cout << "Could't load the file '" << fname << "'!";
    }

    cout << ";) Loaded!" << endl;

    file.close();
  }

  string Map::getName() {
    return name;
  }

  Object* Map::getPlayer () {
    return player;
  }
}
