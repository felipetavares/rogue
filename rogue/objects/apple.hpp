namespace rogue {
  class Apple: public Object {
  private:
  public:
    Apple (Map&, int, int);
    Symbol symbol();
    State state();
    float weight();
    bool isComestible();
    float nutritionValue();
  };
}
