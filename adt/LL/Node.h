#ifndef NODE_H
#define NODE_H

#include<iostream>

template<typename E>
class Node {
private:
  E data;
  Node *next;
  friend class NodeList;
public:
  Node(E data) : data(data),next(NULL) {
  }
  Node() {}
  ~Node() {}
};

#endif /* NODE_H */

