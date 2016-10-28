//## Remove Nth Node From End of List
//### Given a linked list, remove the nth node from the end of list and return its head.
//For example,
//   Given linked list: 1->2->3->4->5, and n = 2.
//   After removing the second node from the end, the linked list becomes 1->2->3->5.
//Note:
//Given n will always be valid.
//Try to do this in one pass.

#include "ll_header.h"


ListNode* removeNthFromEnd(ListNode* head, int n) {

  ListNode *dummy = new ListNode(0);
  dummy->next = head;
  ListNode *h1 = dummy;
  ListNode *h2 = dummy;
  n += 1; //Note 1->2->3 ( 2 ways 
          //1. delete the current node (Avoid copy operation eg. node size 512MB)  
          //2.delete the prev node (adjust pointer)
  while(n != 0) {
    n--;
    h1 = h1->next;
  }
  while(h1 != NULL) {
    h1 = h1->next;
    h2 = h2->next;
  }
  ListNode *tmp = h2->next;
  h2->next = h2->next->next;
  //mem cleanup
  tmp->next = NULL;
  tmp = NULL;
  delete (tmp);
  return dummy->next;
}


int main() {

}


