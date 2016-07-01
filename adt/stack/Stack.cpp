#ifndef MYCLASS_FUNCTIONS
#include "Stack.h"

#else
template <typename E>
Stack<E>::Stack(int cap) : S(new E[cap]), capacity(cap) , t(-1) {

}

template <typename E> 
int Stack<E>::size() const
  { return (t + 1); }                         // number of items in the stack

template <typename E> 
bool Stack<E>::empty() const
  { return (t < 0); }                         // is the stack empty?

template <typename E>                         // return top of stack
const E& Stack<E>::top() const  {
  if (empty()) {
  }
  return S[t];
}

template <typename E>                         // push element onto the stack
void Stack<E>::push(const E& e) {
  if (size() == capacity) {
  }
  S[++t] = e;
}

template <typename E>                         // pop the stack
void Stack<E>::pop()  {
  if (empty()) {
  }
  --t;
}
#endif
