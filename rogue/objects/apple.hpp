namespace rogue {
  class Apple: public Object {
  private:
  public:
    Apple (Map&, int, int);
    Symbol symbol();
    State state();
  };
}
