//Linked List Cycle
//Given a linked list, determine if it has a cycle in it.
//Follow up:
//Can you solve it without using extra space?
//

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

//######################################### 2-pointer - Python######################################### 
//The "trick" is to not check all the time whether we have reached the end but to handle it via an exception. 
//"Easier to ask for forgiveness than permission."
def hasCycle(self, head):
    try:
        slow = head
        fast = head.next
        while slow is not fast:
            slow = slow.next
            fast = fast.next.next
        return True
    except:
        return False

//######################################### 2-pointer - JAVA ######################################### 
public boolean hasCycle(ListNode head) {
    if(head==null) return false;
    ListNode walker = head;
    ListNode runner = head;
    while(runner.next!=null && runner.next.next!=null) {
        walker = walker.next;
        runner = runner.next.next;
        if(walker==runner) return true;
    }
    return false;
}
//######################################### 2-pointer ######################################### 
bool hasCycle(ListNode *head) {
  if(!head) {
      return false;
  }
  ListNode *fast = head->next;
  ListNode *slow = head;
  while(fast != NULL && fast->next != NULL) {
      if(slow == fast) {
          return true;
      }
      fast = fast->next->next;
      slow = slow->next;
  }
  
  return false;
}

//####################################### GOOD ####################################### 
public boolean hasCycle(ListNode head) {
       if(head==null) return false;
       ListNode walker = head;
       ListNode runner = head;
       while(runner.next!=null && runner.next.next!=null) {
           walker = walker.next;
           runner = runner.next.next;
           if(walker==runner) return true;
       }
       return false;
}
//By reverseing list
ListNode* reverseList(ListNode* head) 
{
    ListNode* prev = NULL;
    ListNode* follow = NULL;
    while (head)
    {
        follow = head->next;
        head->next = prev;
        prev = head;
        head = follow;
    }
    return prev;
}
bool hasCycle(ListNode *head)
{
    ListNode* rev = reverseList(head);
    if (head && head->next && rev == head)
    {
        return true;
    }
    return false;
}
