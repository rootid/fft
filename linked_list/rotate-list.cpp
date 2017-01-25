//Rotate Linked List 
//Given a list, rotate the list to the right by k places, where k is non-negative.
//For example:
//Given 1->2->3->4->5->NULL and k = 2,
//return 4->5->1->2->3->NULL.

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

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




//############################################  Ugly ############################################  
int getLength(ListNode *head) {

  int len = 0;
  while(head != NULL) {
    len += 1;
    head = head->next;
  }
 return len; 
}

ListNode* rotateRight(ListNode* head, int k) {

  int idx1 = k;
  ListNode *p = head;
  ListNode *p1 = head;
  ListNode *newHead;
  int l = getLength(head);

  if(!head || (k%l != k) ) {
    return head;
  }
  while(idx1 > 0) {
    if(p == NULL) {
      return head;
    }
    p = p->next;
    idx1 -= 1;
  }
  while(p->next != NULL) {
    p = p->next;
    p1 = p1->next;
  }

  newHead = p1->next;
  p1->next = NULL;

  ListNode *tmp = newHead;
  while(tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = head;

  return newHead;
}
int main() {
  //1->2->3->4->5->NULL,
  ListNode *head = new ListNode(1); 
  head->next = new ListNode(2); 
  head->next->next = new ListNode(3); 
  head->next->next->next = new ListNode(4); 
  head->next->next->next->next = new ListNode(5); 

  cout << "cALL " << endl;
  ListNode *result = rotateRight(head,2);

  cout << "after cALL " << endl;
  while(result != NULL) {
    cout << result->val << " ";
    result = result->next;
  }
  cout << endl;

}
