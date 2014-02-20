namespace rogue {
  class Door: public Object {
  public: enum Direction  {Vertical, Horizontal};
  private:
    Direction dir;
    bool open;
  public:
    Door (Map&, int, int, char);
    Symbol symbol();
    State state();
    bool action(Map&,Action);
    float weight ();
  };
}
