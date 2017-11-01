//Reverse Linked List 

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

//######################################### Iterative - version ######################################### 
public ListNode reverseList(ListNode head) {
    ListNode prev = null;
    while (head != null) {
        ListNode nextHead = head.next;
        head.next = prev;
        prev = head;
        head = nextHead;
    }
    return prev;
}

//######################################### Recursive - version ######################################### 
public ListNode reverseList(ListNode head) {
    return reverseListHelper(null, head);
}

public ListNode reverseListHelper(ListNode prev, ListNode head) {
    if(head == null) return prev;
    ListNode nextHead = head.next; 
    head.next = prev;
    return reverseListHelper(head, nextHead);
}

//######################################### Dummy node approach ######################################### 
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

//######################################### Recursion - Making the head null recursively ######################################### 
public ListNode reverseList(ListNode head) {
    if(head == null || head.next == null) {
        return head;
    }
    ListNode kid = head.next;
    ListNode newHead = reverseList(head.next);
    kid.next = head;
    head.next = null;
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
  ListNode *result = reverseList(head);

  cout << "after cALL " << endl;
  while(result != NULL) {
    cout << result->val << " ";
    result = result->next;
  }
  cout << endl;

}
