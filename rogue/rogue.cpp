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
  
  Object::Object (int x, int y) {
    this->x = x;
    this->y = y;
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
}
