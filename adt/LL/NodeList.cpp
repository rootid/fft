#include "NodeList.h"
#include "Node.h"

//template <typename int>
NodeList::NodeList() : head(NULL)  {}

//template <typename int>
NodeList::~NodeList() {}

//template <typename int>
NodeList::NodeList(int &e) { 
  head = new Node(e);
}

//template <typename int>
bool NodeList:: empty() const {
  return head == NULL;
}

//template <typename int>
void NodeList:: addFront(int &e) {
  Node* newHead = new Node(e);
  newHead->next = head;
  head = newHead;
}

//template <typename int>
int& NodeList:: removeFront() {
  int e = NULL;
  if(!empty()) {
    Node *tmp = head;
    head = head->next;
    e = tmp->data;
    delete tmp;
  }
  return e;
}

//template <typename int>
const int& NodeList:: getFront() const {
  if(!empty())  {
    return head->data;
  }
  return NULL;
}
