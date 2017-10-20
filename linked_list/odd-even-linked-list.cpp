//Odd Even Linked List
//Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.
//You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.
//Example:
//Given 1->2->3->4->5->NULL,
//return 1->3->5->2->4->NULL.
//Note:
//The relative order inside both the even and odd groups should remain as it was in the input. 
//The first node is considered odd, the second node even and so on ...


#include "../headers/global.hpp"
#include "../headers/listnode.hpp"
//########################################################## 
ListNode* oddEvenList(ListNode* head) {
    
    ListNode *odd = head;
    if( !head || !head->next) {
        return head;
    }
    //1->2->3
    ListNode *even = head->next;
    ListNode *even_head = even;
    while(even && even->next) {
        odd->next = odd->next->next;
        even->next = even->next->next;
        odd = odd->next;
        even = even->next;
    }
    odd->next = even_head;
    return head;
}
//########################################################## 
//NOTE : modify head pointer
ListNode* oddEvenList(ListNode* head) {

  if(!head) {
    //cout << "No element found" << "\t" ;
    return head;
  }
  ListNode* oddList = head;
  ListNode* evenList = head->next;
  ListNode* tmpEvenList = evenList ;
  while(oddList && oddList->next) {
    //cout << head->val << "\t" ;
    oddList->next = oddList->next->next;
    evenList->next = evenList->next->next;
    oddList = oddList->next; 
    evenList = evenList->next; 
  }
  //evenList->next = NULL; // PLEASE NOTE : NULL is part of HEAD list
  oddList->next = tmpEvenList;

  return head;
}


//########################################################## 
public ListNode oddEvenList(ListNode head) {
    if (head != null) {
        ListNode odd = head, even = head.next, evenHead = even; 
        while (even != null && even.next != null) {
            odd.next = odd.next.next; 
            even.next = even.next.next; 
            odd = odd.next;
            even = even.next;
        }
        odd.next = evenHead; 
    }
    return head;
}


//########################################################## 
def oddEvenList(self, head):
        if head:
          odd, even, evenHead = head, head.next, head.next
          while even and even.next:
            odd.next, even.next = odd, even = odd.next.next, even.next.next
          odd.next = evenHead
        return head

int main() {
  //1->2->3->4->5->NULL,
  ListNode *head = new ListNode(1); 
  head->next = new ListNode(2); 
  head->next->next = new ListNode(3); 
  head->next->next->next = new ListNode(4); 
  head->next->next->next->next = new ListNode(5); 

  cout << "cALL " << endl;
  ListNode *result = oddEvenList(head);

  cout << "after cALL " << endl;
  while(result != NULL) {
    cout << result->val << " ";
    result = result->next;
  }
  cout << endl;

}
