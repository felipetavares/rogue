namespace rogue {
  class Wall: public Object {
  public: enum Direction  {Vertical, Horizontal};
  private:
    Direction dir;
  public:
    Wall (Map&, int, int, Direction);
    Symbol symbol();
    State state();
  };
}
