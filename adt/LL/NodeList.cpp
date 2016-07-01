#include "NodeList.h"
#include "Node.h"

template <typename E>
NodeList<E>::NodeList() : head(NULL)  {}

template <typename E>
NodeList<E>::~NodeList() {}

template <typename E>
NodeList<E>::NodeList(E &e) { 
  head = new Node<E>(e);
}

template <typename E>
bool NodeList<E>:: empty() const {
  return head == NULL;
}

template <typename E>
void NodeList<E>:: addFront(E &e) {
  Node<E>* newHead = new Node<E>(e);
  newHead->next = head;
  head = newHead;
}

template <typename E>
E& NodeList<E>:: removeFront() {
  E e = NULL;
  if(!empty()) {
    Node<E> *tmp = head;
    head = head->next;
    e = tmp->data;
    delete tmp;
  }
  return e;
}

template <typename E>
const E& NodeList<E>:: getFront() const {
  if(!empty())  {
    return head->data;
  }
  return NULL;
}
