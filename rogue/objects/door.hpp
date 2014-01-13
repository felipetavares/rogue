namespace rogue {
  class Door: public Object {
  public: enum Direction  {Vertical, Horizontal};
  private:
    Direction dir;
    bool open;
  public:
    Door (Map&, int, int, Direction);
    Symbol symbol();
    State state();
  };
}
