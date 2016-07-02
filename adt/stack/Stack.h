#ifndef STACK_H
#define STACK_H

template <typename E>
class Stack
{

  enum { DEF_CAPACITY = 100 };            // default stack capacity
public:
  Stack(int cap = DEF_CAPACITY);        // constructor from capacity
  int size() const;                       // number of items in the stack
  bool empty() const;                     // is the stack empty?
  const E& top() const ;  // get the top element
  void push(const E& e); // push element onto stack
  void pop() ;           // pop the stack
private:                                  // member data
  E* S;                                   // array of stack elements
  int capacity;                           // stack capacity
  int t;                                  // index of the top of the stack
};

#define MY_STACK
#include "Stack.cpp"

#endif /* STACK_H */

