#ifndef NODELIST_H
#define NODELIST_H

#include <iostream>
#include "Node.h"

template <typename E>
class NodeList
{
private:
  Node<E> *head;
public:
  NodeList();
  NodeList(E &e);
  ~NodeList();
  bool empty() const;
  void addFront(E &e);
  E& removeFront();
  const E& getFront() const;
};

#endif /* NODELIST_H */
