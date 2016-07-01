#include<iostream>
using namespace std;
class Base
{
   public:
   virtual void func() const
   {
     cout<<"This is constant base "<<endl;
   }
};

class Derived : public Base
{
   public:
   virtual void func()
   {
     cout<<"This is non constant derived "<<endl;
   }
};

class Derived1 : public Base
{
   public:
   virtual void func() const
   {
     cout<<"This is constant derived "<<endl;
   }
};



int main()
{
  Base *d = new Derived();
  d->func();

  Base *d1 = new Derived1();
  d1->func();
  delete d1;

  return 0;
}
