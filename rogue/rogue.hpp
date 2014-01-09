#ifndef ROGUE_H
#define ROGUE_H

#include <vector>
#include <iostream>
using namespace std;

namespace rogue {
  enum Color {Black,Red,Green,Yellow,Blue,Magneta,Cyan,White};
  enum State {Gas,Liquid,Solid};

  class Map;
  
  class Symbol {
  public:
    Color foreground;
    Color background;
    char character;  
    
    Symbol();
    Symbol(Color,char);
    Symbol(Color,Color,char);
    void draw();
  };
  
  class Object {
  public:
    enum Type {tWall};
  private:
    int x,y;
    Type type;
  public:
    Object (int,int,Type);
    Type objectType ();
    
    virtual void think () {};
    virtual Symbol symbol () {};
    virtual State state () {};
    virtual void onMove (Map&, int, int) {};
};
  
  class Map {
    int w,h;
    vector <Object*> **data;
  public:
    Map(int,int);
    void draw();
    ~Map();
  };

  class Wall: public Object {
  public:
    Wall (int x, int y):
      Object(x,y,Object::tWall) {
    }
  };
}

#endif /* ROGUE_H */
  
