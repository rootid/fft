#ifndef NODint_H
#define NODint_H

#include<iostream>

template<class E>
class Node {
private:
  int data;
  Node *next;
  friend class NodeList;
public:
  Node(E data) : data(data),next(NULL) {
  }
  Node() {}
  ~Node() {}
};

#endif /* NODint_H */

