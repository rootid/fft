//Delete Node in a Linked List
//
//Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
//Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.
//

//1->2->3->4->5
#include<iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void deleteNodeWoMemoryLeak(ListNode* node) {
    node->val = node->next->val;
    ListNode* t = node->next;
    node->next = t->next;
    delete t;
}

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
