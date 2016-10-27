#define DISALLOW_EVIL_CONSTRUCTORS(ClassName) \ 
    ClassName(const ClassName&); \ 
    void operator=(const ClassName&);

class Test {
  private:
    DISALLOW_EVIL_CONSTRUCTORS(Test);
  public:

};
