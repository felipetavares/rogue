namespace rogue {
  class Player: public Object {
  public:
    Player (Map&, int, int);
    Symbol symbol();
    State state();
    void move (Map&,int,int);
  };
}
