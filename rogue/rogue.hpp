#ifndef ROGUE_H
#define ROGUE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace rogue {
  enum Color {Black=0,Red=1,Green=2,Yellow=3,Blue=4,Magneta=5,Cyan=6,White=7};
  enum State {Gas=0,Liquid,Solid};

  class Map;
  
  class Symbol {
  public:
    Color foreground;
    Color background;
    string character;  
    
    Symbol();
    Symbol(Color,string);
    Symbol(Color,Color,string);
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
    virtual void move (Map&, int, int);
};
  
  class Map {
    int w,h;
  public:
    vector <Object*> **data;
  public:
    Map(int,int);
    ~Map();
    void draw();
    bool inside(int,int);
  };
}

#endif /* ROGUE_H */
