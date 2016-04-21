//Rotate Linked List 
//Given a list, rotate the list to the right by k places, where k is non-negative.
//For example:
//Given 1->2->3->4->5->NULL and k = 2,
//return 4->5->1->2->3->NULL.

#include<iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

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
