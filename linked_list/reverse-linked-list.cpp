//Reverse Linked List 

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"


//######################################### Iterative - version ######################################### 
 public ListNode reverseList(ListNode head) {
        if(head == null || head.next == null) return head;
        ListNode tmp = head;
        ListNode prev = null;
        ListNode child = null;
        while(tmp != null) {
            child = tmp.next;
            tmp.next = prev;
            prev = tmp;
            tmp = child;
        }
        return prev;
    }

//######################################### Recursive  - version ######################################### 
private ListNode reverseList(ListNode prev, ListNode head) {      
    if(head == null) return prev;
        ListNode child  = head.next; 
        head.next = prev;
     return reverseList(head, child);
}

public ListNode reverseList(ListNode head)  {
    return reverseList(null, head);
}

//######################################### Recursive  - version ######################################### 
public class Solution {
    public ListNode reverseList(ListNode head) {
        if(head == null ||head.next == null){ //empty / single node
            return head;
        }
        ListNode rest = reverseList(head.next); //head.next
        head.next.next = head; //Overwrite 3rd node with 1st node, base case checks for head.next
        head.next = null;
        return rest; //return the rest
    }
}
//######################################### Iterative - version ######################################### 
public ListNode reverseList(ListNode current) {
   if(current == null) return null;
   ListNode prev = null;
   while(current != null) { //1->2->null
       ListNode rest = current.next; //Store next r=c.next=p=c=r
       current.next = prev; //Change next -> Copy from previous
       prev = current; //Overwrite previous
       current = rest; //Restore next
   }
 return prev;
}

//######################################### Recursive - version ######################################### 
public ListNode reverseList(ListNode head) {
    return reverseListHelper(null, head);
}

public ListNode reverseListHelper(ListNode prev, ListNode head) {
    if(head == null) return prev;
    ListNode rest  = head.next; 
    head.next = prev;
    return reverseListHelper(head, rest);
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
/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
