//Linked List Cycle II 
//Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
//Note: Do not modify the linked list.
//Follow up:
//Can you solve it without using extra space?



//##################### Set - Keep track of nodes ##################### 
//SC - O(n), TC - O(1)
public ListNode detectCycle(ListNode head) {
    if(head == null || head.next == null) return null;
    Set<ListNode> hs = new HashSet<>();
    while(head != null) {
        if(hs.contains(head)) return head;
        hs.add(head);
        head = head.next;
    }
    return null;
}

//##################### Iteration + Floyd cycle detection ##################### 
public ListNode detectCycle(ListNode head) { 
    if(head == null || head.next == null) return null;
    ListNode fast = head;
    ListNode slow = head;
    while(fast != null && fast.next != null) {
        fast = fast.next.next;
        slow = slow.next;
        if(fast == slow) break;
    }
    if(fast == slow) {
        ListNode tmp = head;
        while(tmp != fast) {
            tmp = tmp.next;
            fast = fast.next;
        }
        return fast;
    }
    return null;
}
//##################### c++ ##################### 
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

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
