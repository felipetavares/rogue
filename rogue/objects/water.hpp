namespace rogue {
  class Water: public Object {
  public: enum Direction  {Vertical, Horizontal};
  private:
    Direction dir;
  public:
    Water (Map&, int, int);
    Symbol symbol();
    State state();
  	float weight();
  };
}