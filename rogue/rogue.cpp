#include "rogue.hpp"

namespace rogue {
  // Init a symbol
  Symbol::Symbol () {
    foreground = White;
    background = Red;
    character = ' ';
  }
  
  Symbol::Symbol (Color foreground, char character) {
    this->foreground = foreground;
    this->character = character;
  }
  
  Symbol::Symbol (Color foreground, Color background, char character) {
    this->foreground = foreground;
    this->background = background;
    this->character = character;
  }
  
  void Symbol::draw () {
    cout << "\33[3";
    cout << (int)foreground;
    cout << "m";
    cout << "\33[4";
    cout << (int)background;
    cout << "m";
    cout << character;
    cout << "\33[0m";
  }
  
  Object::Object (int x, int y, Type type) {
    this->x = x;
    this->y = y;
    this->type = type;
  }
  
  Object::Type Object::objectType () {
	return this->type;
  }
  
  Map::Map (int w, int h):
    data(NULL) {
    this->w = w;
    this->h = h;
    
    data = new vector <Object*>*[h];
    for (int i=0;i<h;i++) {
      data[i] = new vector <Object*>[w];
      data[i][0].push_back(new Wall(0,i));
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
	  cout << " ";
	} 
      }
      cout << endl;
    }
  }
}
