//Delete Node in a Linked List
//
//Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
//Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.
//
//1->2->3->4->5
//
#include "../headers/global.hpp"
#include "../headers/listnode.hpp"


//######################################### Update val, reference ######################################### 
public void deleteNode(ListNode node) {
    node.val = node.next.val;
    ListNode savedNextRef = node.next;
    node.next = node.next.next;
    savedNextRef = null;
}

//######################################### Update val, reference ######################################### 
public void deleteNode(ListNode node) {
     node.val = node.next.val;
     node.next = node.next.next;
}

//######################################### W/o memory leak ######################################### 
void deleteNodeWoMemoryLeak(ListNode* node) {
    node->val = node->next->val;
    ListNode* t = node->next;
    node->next = t->next;
    delete t;
}

//######################################### W/ memory leak ######################################### 
void deleteNode(ListNode* node) {
  if(node->next == NULL)  {
    node = NULL;
    delete node;
    //node = node->next;
    return;
  }
  node->val = node->next->val;
  node->next = node->next->next;
}

//######################################### With Memory leak  ######################################### 
void deleteNode(ListNode* node) {
    *node = *node->next;
}

//######################################### With auto ######################################### 
void deleteNode(ListNode* node) {
    auto next = node->next;
    *node = *next;
    delete next;
}

//######################################### Copy value + and check wheather it is last node######################################### 
public void deleteNode(ListNode node) {
  node.val = node.next.val;  
  if(node.next == null) node = null;
  else node.next = node.next.next;
}

int main() {
  //1->2->3->4->5->NULL,
  ListNode *head = new ListNode(1); 
  head->next = new ListNode(2); 
  head->next->next = new ListNode(3); 
  //head->next->next->next = new ListNode(4); 
  //head->next->next->next->next = new ListNode(5); 

  cout << "cALL " << endl;

  //deleteNode(head);
  deleteNode(head->next->next);

  cout << "after cALL " << endl;
  while(head != NULL) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;

}
/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
