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
