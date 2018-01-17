#ifndef NODintLIST_H
#define NODintLIST_H

#include <iostream>
#include "Node.h"

//template <typename int>
class NodeList
{
private:
  //Node<int> *head;
  Node *head;
public:
  NodeList();
  NodeList(int &e);
  ~NodeList();
  bool empty() const;
  void addFront(int &e);
  int& removeFront();
  const int& getFront() const;
};

#endif /* NODintLIST_H */
