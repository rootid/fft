//Rotate Linked List
//Given a list, rotate the list to the right by k places, where k is non-negative.
//For example:
//Given 1->2->3->4->5->NULL and k = 2,
//return 4->5->1->2->3->NULL.

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"



//############################################  Iteration  ############################################
public ListNode rotateRight(ListNode head, int k) {
      ListNode fake = new ListNode(-1), slow = fake, fast = fake;
      fake.next = head;

      int len = 0;
      while(fast.next != null){   // fast REACH tail && Count len
          fast = fast.next; len++;
      }
      if(len == 0) return null;   // CHECK null
      k %= len; //To avoid cycle

      for(int i=0; i<len-k; i++)  // slow REACH before the rotated point
          slow = slow.next;

      fast.next = fake.next;      // CONNECT
      fake.next = slow.next;
      slow.next = null;

      return fake.next;
}

//############################################  Iteration  ############################################
public ListNode rotateRight(ListNode head, int k) {
    if(head == null) return head;
    int len = 0;
    ListNode fp = head, lp = head, tmp = head;
    while(tmp != null) {
        tmp = tmp.next;
        len++; //1. Get the length
    }
    k = k % len;  //To avoid cycle
    k = len - k -1; //traverse till end of first part
    while(k-- != 0) head = head.next;
    fp = head.next; // fp is next of HEAD
    head.next = null; // HEAD next is null NOTE : head next and next of HEAD are different.
    if(fp == null) return lp; //K == len
    tmp = fp; //points to kth node
    while(tmp.next != null) tmp = tmp.next; //End of list
    tmp.next = lp; //Connect last part of list with HEAD/ Future last part
    return fp;
}

//############################################  GOOD ############################################
ListNode* rotateRight(ListNode* head, int k) {

  if(!head) {
    return head;
  }
  ListNode *newHead = head;
  ListNode *tail = head;
  int count = 1;
  while(tail->next != NULL) {
    tail = tail->next;
    count += 1;
  }
  tail->next = head; //create circular LL
  k = k%count;
  if(k) {
    for(int i=0;i<count-k;i++) {
      tail = tail->next;
    }
  }
  newHead = tail->next;
  tail->next = NULL;
  return newHead;
}

//############################################  GOOD ############################################
int getLength(ListNode *head) {
  int len = 0;
  while(head != NULL) {
    len += 1;
    head = head->next;
  }
 return len;
}

ListNode* reverse(ListNode* head, int m,int n) {
  ListNode *prev = head;
  while(m > 0) {
    m -= 1;
    prev = prev->next;
  }
  ListNode *current = prev;
  ListNode *nxt = current;
  //reverse from m to n
  while (n > 0) {
    nxt = current->next;
    current->next = prev;
    prev = current;
    current = nxt;
    n = n -1;
  }
  return prev;
}

ListNode* rotateRight(ListNode* head, int k) {

  if(!head) {
    return head;
  }
  ListNode *newHead = head;
  int len = getLength(head);
  k = k%len;

  if(k != 0) {
    head = reverse(head,1,k-1);
    head = reverse(head,k,len);
    head = reverse(head,1,len);
  }
  return head  ;
}



/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
