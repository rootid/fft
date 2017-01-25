//Reverse Linked List 

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

//Addition of node solution
ListNode* reverseList(ListNode* head) {
        ListNode* new_head = new ListNode(0);
        new_head->next = head;
        ListNode* pre = new_head;
        ListNode* cur = head; 
        while (cur && cur->next) {
            ListNode* temp = pre->next;
            pre->next = cur->next;
            cur->next = cur->next->next; 
            pre->next->next = temp;
        }
        return new_head->next;
}

ListNode* reverseListRec(ListNode* head) {

  //1-2 ==> 2-1

  if(!head || !head->next) {
    return head;
  }
  ListNode *nextP = reverseListRec(head->next);
  nextP->next->next = head; 
  head->next = NULL;
  return nextP;
}

ListNode* reverseList(ListNode* head) {

  if(!head) {
    return head;
  }
  //1-2 ==> 2-1
  ListNode *prev = NULL;
  ListNode *nextP = NULL;
  ListNode *current = head;
  while(current != NULL) {
    nextP = current->next;
    current->next = prev;
    nextP->next = current;
    prev = current;
    current = nextP;
  }
  head = prev;
  return head;
}

int main() {
  //1->2->3->4->5->NULL,
  ListNode *head = new ListNode(1); 
  head->next = new ListNode(2); 
  head->next->next = new ListNode(3); 
  head->next->next->next = new ListNode(4); 
  head->next->next->next->next = new ListNode(5); 

  cout << "cALL " << endl;
  ListNode *result = reverseList(head);

  cout << "after cALL " << endl;
  while(result != NULL) {
    cout << result->val << " ";
    result = result->next;
  }
  cout << endl;

}
