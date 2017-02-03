//Reorder List
//Given a singly linked list L: L0→L1→…→Ln-1→Ln,
//reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
//You must do this in-place without altering the nodes' values.
//For example,
//Given {1,2,3,4}, reorder it to {1,4,2,3}.
//


//L : l0->l1->l2->.....->ln-1->ln
//l0->ln->l1->ln-1
//In place w/o altering the node values
//1. break the list into half
//2. reverse the second half
//3. merge the linked list alternatively.
//

//##################### replaced length computation ##################### 
void reorderList(ListNode *head) {
  if (head == NULL || head->next == NULL)  {
    return;
  }
  ListNode* slow = head;
  ListNode* fast = head;
  // Find the middle node using the '2-pointer' technique
  while (fast->next!=NULL) {
      slow = slow->next;
      fast = fast->next;
      if (fast->next!=NULL) {
        fast = fast->next;
      }
  }
  // Reverse the second half
  ListNode* prev = slow;
  ListNode* cur = slow->next;
  ListNode* next; 
  while (cur != NULL) {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
  }
  slow->next = NULL; // The middle node should point to null

  // Reorder the list
  // prev and cur are approaching the middle node 
  // from the two ends of the linked list
  cur = prev;
  prev = head;
  while (prev != cur) {
      next = prev->next;
      prev->next = cur;
      prev = cur;
      cur = next;
  }
}

//##################### Linking during recursion  ##################### 
void reorderList(ListNode* head) {
        if(head==NULL || head->next==NULL)  return;
        bool flag = false;
        reOrder(flag, &head, head);
}
void reOrder(bool& flag , ListNode** head, ListNode* tail){
    if(tail==NULL)  return;
    reOrder(flag,head,tail->next);
    
if(!flag){
    if((*head)->next==tail || (*head) == tail){
          tail->next = NULL;
          flag = true; // break chaining
          return;
      }
      tail->next = (*head)->next;
      (*head)->next = tail;
      *head = tail->next;
	}
}
//##################### with Stack ##################### 
void reorderList(ListNode* head) {
    if(!head)
    {
        return;
    }
    ListNode* slow = head, *fast = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    
    stack<ListNode*> secondHalf;
    
    while(slow)
    {
        secondHalf.push(slow);
        slow = slow->next;
    }
    
    slow = head;
    for(;;)
    {
        ListNode* last = secondHalf.top();
        secondHalf.pop();
        if(last == slow || secondHalf.empty())
        {
            last->next = NULL;
            return;
        }
        ListNode* next = slow->next;
        slow->next = last;
        last->next = next;
        slow = next;
    }
}

//##################### Bad ##################### 
ListNode *reverseList (ListNode *head) {
    if (head == 0) {
        return head;
    }
    ListNode* current = head;
    ListNode* prev = 0;
    ListNode* front = 0;
    while (current != 0) {
        front = current->next;
        current->next = prev;
        prev = current;
        current = front;
    }
   return prev; 
}

ListNode *reorderList (ListNode* head) {
    int len = 0;
    if (head == 0 || head->next == 0) {
        return head;
    }
    ListNode *tmp = head;
    while (tmp != 0) {
        tmp = tmp->next;
        len++;    
    }
    int half_len = len / 2;
    ListNode *h1 = head;
    while (half_len > 0) {
        h1 = h1->next;
        half_len -= 1;
    }
    ListNode *h2 = h1->next;
    h1->next = NULL;
    ListNode* h2_rev = reverseList (h2);
    half_len = len / 2;
    ListNode* tmp_head = head;
    while (half_len > 0 && h2_rev) {
        ListNode* tmp_next = tmp_head->next;
        tmp_head->next = h2_rev;
        ListNode* h2_next = h2_rev->next;
        h2_rev->next = tmp_next;
        tmp_head = tmp_next;
        h2_rev = h2_next;
        half_len -= 1;
    }
    return head;
}
//############################################# diff functions ############################################# 
ListNode* reverseList(ListNode* head){
    if (head==NULL || head->next==NULL) return head;
    ListNode *pre=head, *cur=pre->next, *post;
    pre->next = NULL;
    while (cur!=NULL){
        post = cur->next;
        cur->next = pre;
        pre = cur;
        cur = post;
    }
    return pre;
}
void mergeList(ListNode* L1, ListNode *L2){
    ListNode *cur1=L1, *cur2=L2,*post1,*post2;
    while(cur2!=NULL){
        post1 = cur1->next;
        post2 = cur2->next;
        cur1->next = cur2;
        cur2->next = post1;
        cur1 = post1;
        cur2 = post2;
    }
}
void reorderList(ListNode* head) {
    if (head==NULL || head->next==NULL || head->next->next==NULL) return;
    ListNode *slow=head,*fast=head;
    while(fast->next!=NULL && fast->next->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    ListNode *head2 = slow->next;
    slow->next = NULL;
    mergeList(head,reverseList(head2));
}
