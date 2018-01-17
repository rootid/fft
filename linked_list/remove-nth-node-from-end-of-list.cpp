//## Remove Nth Node From End of List
//### Given a linked list, remove the nth node from the end of list and return its head.
//For example,
//   Given linked list: 1->2->3->4->5, and n = 2.
//   After removing the second node from the end, the linked list becomes 1->2->3->5.
//Note:
//Given n will always be valid.
//Try to do this in one pass.

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

//############################### Iteration -2 Pointers ###############################  
//TC : O(L)
public ListNode removeNthFromEnd(ListNode head, int n) {
    ListNode dummy = new ListNode(0);
    dummy.next = head;
    ListNode first = dummy;
    ListNode second = dummy;
    // Advances first pointer so that the gap between first and second is n nodes apart
    for (int i = 1; i <= n + 1; i++) {
        first = first.next; //got upto n+1 distance
    }
    // Move first to the end, maintaining the gap
    while (first != null) {
        first = first.next;
        second = second.next;
    }
    second.next = second.next.next;
}

//############################### Iteration ###############################  
//Time complexity : O(L).
public ListNode removeNthFromEnd(ListNode head, int n) {
    ListNode dummy = new ListNode(0);
    dummy.next = head;
    int distanceFromHead  = 0;
    ListNode first = head;
    while (first != null) {
        distanceFromHead++;
        first = first.next;
    }
    distanceFromHead -= n; //
    first = dummy;
    while (distanceFromHead > 0) {
        distanceFromHead--;
        first = first.next;
    }
    first.next = first.next.next;
    return dummy.next;
}

//###############################  Recursion ###############################  
//[1] , 1 o/p []
public ListNode removeNthFromEnd(ListNode head, int n) {
    int m = getLength(head);
    int fromHeadDist = m - n;
    return removeNodeFromStart(head, fromHeadDist);
}
private ListNode removeNodeFromStart(ListNode head, int n) {
    if(n == 0) 
        if(head != null) return head.next;
    head.next = removeNodeFromStart(head.next, n-1);
    return head; 
}
private int getLength(ListNode head) {
    int cnt = 1;
    while(head.next != null) {
        head= head.next;
        cnt++;
    }
    return cnt;
}

//###############################  Iteration ###############################  
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

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
