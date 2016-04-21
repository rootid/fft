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
