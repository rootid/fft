//Linked List Cycle II 
//Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
//Note: Do not modify the linked list.
//Follow up:
//Can you solve it without using extra space?




ListNode *detectCycle(ListNode *head) {

  if(!head ) { 
    return head;
  }
  ListNode* walker = head;
  ListNode* runner = head;
  while(runner->next != NULL && runner->next->next != NULL) {
      walker = walker->next;
      runner = runner->next->next;
      if(walker == runner)  {
        ListNode *tmp = head;
        while(runner != tmp) { // for dx = 0 case
          runner = runner->next;
          tmp = tmp->next;
        }
        return tmp;
      }
  }
  return NULL;
}



