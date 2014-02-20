namespace rogue {
  class Player: public Object {
  	vector<Object*> inventory;
    
    // All player CHARACTERISTICS begin with c
    float cWeight;
    float cEnergy;
  public:
    Player (Map&, int, int);
    Symbol symbol();
    State state();
    void move (Map&,int,int,bool=false);
    void pickup (Object*);
    vector <Object*> drop();
    float weight();
    void displayInventory();
    void displayCharacteristics();
    bool canPickup(Object*);
    float inventoryWeight();
    void eat();
    bool alive();
  };
}
