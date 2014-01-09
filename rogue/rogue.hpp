#ifndef ROGUE_H
#define ROGUE_H

#include <vector>
using namespace std;

namespace rogue {
  enum Color {Black,Red,Green,Yellow,Blue,Magneta,Cyan,White};
  enum State {Gas,Liquid,Solid};

  class Map;
  
  class Symbol {
  public:
    Color foreground;
    Color background;
    wchar_t character;  
    
    Symbol();
    Symbol(Color,wchar_t);
    Symbol(Color,Color,wchar_t);
  };
  
  class Object {
    int x,y;
    Type type;
  public:
    enum Type {};
    Object (int,int);
    
    virtual void think () {};
    virtual Symbol symbol () {};
    virtual State state () {};
    virtual void onMove (Map&, int, int) {};
    virtual Type objectType ();
};
  
  class Map {
    int w,h;
    vector <Object*> **data;
  public:
    Map(int,int);
    ~Map();
  };
}

#endif /* ROGUE_H */
  
