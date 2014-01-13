#include <algorithm>
#include "rogue.hpp"
#include "objects/wall.hpp"

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

  void Object::move (Map& map, int dx, int dy) {
    vector <Object*> &v = map.data[y][x];
    v.erase(remove(v.begin(), v.end(), this), v.end());    
    if (map.inside(dx,dy)) {
      map.data[dy][dx].push_back(this);
      x = dx;
      y = dy;
    }
  }

  void Object::completeDescription () {
    cout << name << endl;
  }

  int Object::getX() {
    return x;
  }

  int Object::getY() {
    return y;
  }
  
  Map::Map (int w, int h):
    data(NULL) {
    this->w = w;
    this->h = h;
    
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

  vector <Object*> Map::at (Object *o) {
    if (inside (o->getX(), o->getY())) {
      return data[o->getY()][o->getX()];
    }
  }

  bool Map::inside (int x, int y) {
    if (x >= 0 && y >= 0 &&
	x < w  && y < h)
      return true;
    return false;
  }
}
