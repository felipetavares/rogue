#ifndef ROGUE_H
#define ROGUE_H

#include <vector>
#include <string>
#include <iostream>
#include "properties/properties.hpp"
using namespace std;

namespace rogue {
  enum Color {Black=0,Red,Green,Yellow,Blue,Magneta,Cyan,White};
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
    enum Type {tWall,tPlayer,tDoor,tApple,tGrass,tWater};
    enum Action {aOpen,aClose};
  protected:
    int x,y;
    Type type;
    string name;
    vector <Propertie> properties;
  public:
    Object (Map&,int,int,Type,string);
    Type objectType ();
    int getX();
    int getY();
    void completeDescription();

    string getName();

    virtual void think () {};
    virtual Symbol symbol () {};
    virtual State state () {};
    virtual float weight() = 0;
    virtual void move (Map&, int, int, bool=false);
    virtual bool action (Map&, Action) {return false;};
    virtual bool canPickup (Object*) {return true;};
    virtual bool isComestible () {return false;};
    virtual float nutritionValue() {return 0;};
  };
  
  class Map {
    int w,h;
    string name;
    Object* player;
    vector <Object*> vnull;
  public:
    vector <Object*> **data;
  public:
    Map(string);
    Map(int,int,string);
    ~Map();
    void draw();
    bool inside(int,int);
    vector <Object*> &at (Object*);
    vector <Object*> &at (int,int);
    string getName();
    Object *getPlayer();
  };
}

#endif /* ROGUE_H */
