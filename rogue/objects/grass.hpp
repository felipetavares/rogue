namespace rogue {
  class Grass: public Object {
  public: enum Direction  {Vertical, Horizontal};
  private:
    Direction dir;
  public:
    Grass (Map&, int, int);
    Symbol symbol();
    State state();
  	float weight();
  };
}