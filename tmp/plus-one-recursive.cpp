//Plus One Linked List
//Given a non-negative number represented as a singly linked list of digits, plus one to the number.
//The digits are stored such that the most significant digit is at the head of the list.
//Example:
//Input:
//1->2->3
//Output:
//1->2->4

ListNode* plusOne(ListNode* head) {
      ListNode *newHead = new ListNode(0);
      newHead->next = head;
      ListNode *p = newHead, *q = head;
      
      while (q) {
          if (q->val != 9)
              p = q;
          q = q->next;
      }
      
      ++(p->val);
      p = p->next;
      while (p) {
          p->val = 0;
          p = p->next;
      }
      
      if (newHead->val)
      	head = newHead;
      else
      	delete newHead;
      
      return head;
  }
