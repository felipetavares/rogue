#include "rogue.hpp"

namespace rogue {
  // Init a symbol
  Symbol::Symbol () {
    foreground = White;
    background = Black;
    character = ' ';
  }
  
  Symbol::Symbol (Color foreground, wchar_t character) {
    this->foreground = foreground;
    this->character = character;
  }
  
  Symbol::Symbol (Color foreground, Color background, wchar_t character) {
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
  }
  
  Object::Object (int x, int y, Type type) {
    this->x = x;
    this->y = y;
    this->type = type;
  }
  
  Type Object::objectType () {
	return this->type;
  }
  
  Map::Map (int w, int h):
    data(NULL) {
    this->w = w;
    this->h = h;
    
    data = new vector <Object*>*[h];
    for (int i=0;i<h;i++) {
      data[i] = new vector <Object*>[w];
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
