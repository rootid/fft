//Remove Duplicates from Sorted List II
//Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
//For example,
//Given 1->2->3->3->4->4->5, return 1->2->5.
//Given 1->1->1->2->3, return 2->3.
//################################## Recusrion - 1 ################################## 
ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next) {
      return head;
    }
    int val = head->val;
    ListNode* p = head->next;
    //compare 2 values at a time 
    if (p->val != val) {
        head->next = deleteDuplicates(p);
        return head;
    } else {
        while (p && p->val == val) {
          p = p->next;
        }
        return deleteDuplicates(p);
    }
}
//################################## Recusrion - 2 ################################## 
ListNode* deleteDuplicates(ListNode* head) {
    if(!head || !head->next) {
      return head;
    }
    auto run = head->next;
    while(run && run->val == head->val) {
      run = run->next;
    }
    if(run != head->next) {
      return deleteDuplicates(run);
    }
    head->next = deleteDuplicates(run);
    return head;
}

//################################## dummy iterative ################################## 
ListNode* deleteDuplicates(ListNode* head) { 
  ListNode *dummy_head = new ListNode(0);
  dummy_head->next = head;
  ListNode* tmp = dummy_head;
  while(tmp->next && tmp->next->next) { 
     int next_val = tmp->next->val;
     if (tmp->next->val == tmp->next->next->val) {
     int duplicate = tmp->next->val;
     while (tmp->next && tmp->next->val == duplicate) {
       tmp->next = tmp->next->next; 
     } 
     } else {
      tmp = tmp->next; 
     } 
  }
  return dummy_head->next;
}
