

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

//better
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


