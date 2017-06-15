//Plus One Linked List
//Given a non-negative number represented as a singly linked list of digits, plus one to the number.
//The digits are stored such that the most significant digit is at the head of the list.
//Example:
//Input:
//1->2->3
//Output:
//1->2->4

//################################ Recursive ################################ 
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

//################################ Iterative ################################ 
int addOne(ListNode *head) {
    //for empty node add one to the node
    if(!head) {
        return 1;
    }
    int carry = addOne(head->next);
    int val = head->val;
    //if last node or if got carry
    //if(head->next == NULL || carry == 1) {
    if(carry == 1) {
        val += 1;
        head->val = val % 10;
    }
    return (val/10);
}
ListNode* plusOne(ListNode* head) {
     if(addOne (head) == 1) {
        ListNode* tmp = new ListNode(1);
        tmp->next = head;
        head = tmp;
     }
     return head;
}
//another to express the helper function
int addOne_helper(ListNode *head) {
     if(!head) {
         return 1;
     }
     if(addOne(head->next) == 1 ) {
         int carry = (head->val + 1) / 10;
         head->val = (head->val + 1) %10;
         return (carry);
     }
     return 0;
}

int main () {
}
