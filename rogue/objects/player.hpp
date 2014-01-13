namespace rogue {
  class Player: public Object {
  	vector<Object*> inventory;
  public:
    Player (Map&, int, int);
    Symbol symbol();
    State state();
    void move (Map&,int,int);
    void pickup (Object*);
    vector <Object*> drop();

    void displayInventory();
  };
}
