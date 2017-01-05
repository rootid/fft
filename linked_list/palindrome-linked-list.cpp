//Palindrome Linked List
//Given a singly linked list, determine if it is a palindrome.
//Follow up:
//Could you do it in O(n) time and O(1) space?

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

//############################## REV LIST (GOOD) ############################## 
bool isPalindrome(ListNode* head) {
      ListNode* slow = head;
      ListNode* fast = head;
      ListNode *prev = NULL;
      while(fast && fast->next) {
          ListNode *tmp = slow;
          fast = fast->next->next;
          slow = slow->next;
          tmp->next= prev;
          prev = tmp;
      }
      if(fast) {
           slow = slow->next; // single element & odd element
      }
      
      while(slow && prev->val == slow->val) {
          slow = slow->next;
          prev = prev->next;
      }
      return slow == NULL;
}
//############################## Recusrive (GOOD) ############################## 
bool pal_helper(ListNode*& head,ListNode* last) {
    if(!last) {
        return true;
    }
    bool is_pal = pal_helper(head,last->next);
    if(head->val != last->val) {
        return false;
    }
    head = head->next;
    return is_pal;
}
bool isPalindrome(ListNode* head) {
    return pal_helper(head,head);
}
