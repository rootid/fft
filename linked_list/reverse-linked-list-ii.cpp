//Reverse Linked List II
//Reverse a linked list from position m to n. Do it in-place and in one-pass.
//For example:
//Given 1->2->3->4->5->NULL, m = 2 and n = 4,
//return 1->4->3->2->5->NULL.
//Note:
//Given m, n satisfy the following condition:
//1 ≤ m ≤ n ≤ length of list.
//
ListNode* reverseBetween(ListNode* head, int m, int n) {
      int idx = 0;
      ListNode* dummy_head = new ListNode(0);
      dummy_head->next = head;
      ListNode* prev = dummy_head;
      while(idx < m-1) {
         prev = prev->next;
         idx++;
     }
    // if(prev) {
    idx = 0;
    ListNode* cur = prev->next;
    while(idx < n-m) {
        ListNode *tmp = cur->next;
        cur->next = tmp->next;
        tmp->next = prev->next;
        prev->next = tmp;
        idx++;
    }
    // }
   return dummy_head->next; 
}
//####################### Avoid memory leak  ####################### 
ListNode* reverseBetween(ListNode* head, int m, int n) {
       
       if (head == NULL || m == n) return head;
       
       ListNode dummy(0); // aviod memory leak;
       dummy.next = head;
       
       ListNode *pre = &dummy;
       int diff = n - m;
       
       // decreaes m, then check if m > 0
       while(--m) pre = pre->next;
       
       ListNode *cur = pre->next; 
       ListNode *curNext = cur->next;
       
       // rotating the nodes that need to be reversed.
       while (diff--){
           ListNode* rot = curNext;
           curNext = curNext->next;
           cur->next = curNext;
           rot->next = pre->next;
           pre->next = rot;
       }
       return dummy.next;
}

//####################### W/O dummy head ####################### 
ListNode *reverseBetween(ListNode *head, int m, int n) {
        ListNode *prev = NULL;
        ListNode *tail = head;
        int move = m - 1;
        while (move-- > 0) {
            prev = tail; tail = tail->next;
        }
        int num = n - m;
        ListNode *front = tail;
        while (num-- > 0) {
            ListNode *tmp = tail->next;
            tail->next = tmp->next;
            tmp->next = front;
            front = tmp;
            if (prev) {
                prev->next = front;
            }
        }
        if (prev) {
            return head;
        } 
        return front;
} 

//####################### ####################### 
ListNode *reverseBetween(ListNode *head, int m, int n) {
   if(m==n) {
     return head; 
   }
   n-=m;
   ListNode prehead(0);
   prehead.next=head;
   ListNode* pre=&prehead;
   while(--m) {
     pre=pre->next;        
   }
   ListNode* pstart = pre->next;
   while(n--) {
       ListNode *p = pstart->next;
       pstart->next = p->next;
       p->next = pre->next;
       pre->next = p;
   }
   return prehead.next;
}
