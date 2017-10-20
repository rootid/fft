//Palindrome Linked List
//Given a singly linked list, determine if it is a palindrome.
//Follow up:
//Could you do it in O(n) time and O(1) space?

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

//############################## Iterative + recursive Reverse list  ############################## 
public boolean isPalindrome(ListNode head) {
    ListNode fast = head, slow = head;
    while (fast != null && fast.next != null) {
        fast = fast.next.next;
        slow = slow.next;
    }
    if (fast != null) { // odd nodes: let right half smaller
        slow = slow.next;
    }
	//Reverse the second half
    slow = reverse(slow);
    fast = head;
    
    while (slow != null) {
        if (fast.val != slow.val) {
            return false;
        }
        fast = fast.next;
        slow = slow.next;
    }
    return true;
}

public ListNode reverse(ListNode head) {
    ListNode prev = null;
    while (head != null) {
        ListNode next = head.next;
        head.next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

//############################## Recusrive ############################## 
ListNode globalHead = null;
boolean isPalindromeHelper(ListNode last) {
    if(last == null) {
        return true;
    }
    boolean isPalindrome = isPalindromeHelper(last.next);
    if(globalHead.val != last.val) {
        return false;
    }
    globalHead = globalHead.next;
    return isPalindrome;
}
boolean isPalindrome(ListNode head) {
    globalHead = head;
    return isPalindromeHelper(head);
}

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

//############################## Recursive - python ############################## 
//O(n) time, O(1) space. The second solution restores the list after changing it.
//Solution 1: Reversed first half == Second half?
//Phase 1: Reverse the first half while finding the middle.
//Phase 2: Compare the reversed first half with the second half.

//############################## Recursive - python ############################## 
def isPalindrome(self, head):
    rev = None
    slow = fast = head
    while fast and fast.next:
        fast = fast.next.next
        rev, rev.next, slow = slow, rev, slow.next  # That first evaluates the right side and then assigns to the left side from left to right
    if fast:
        slow = slow.next
    while rev and rev.val == slow.val:
        slow = slow.next
        rev = rev.next
    return not rev

//Solution 2: Play Nice
//Same as the above, but while comparing the two halves, restore the list to its original state by reversing the first half back. Not that the OJ or anyone else cares.

//############################## Recursive - python ############################## 
def isPalindrome(self, head):
    rev = None
    fast = head
    while fast and fast.next:
        fast = fast.next.next
        rev, rev.next, head = head, rev, head.next
    tail = head.next if fast else head
    isPali = True
    while rev:
        isPali = isPali and rev.val == tail.val
        head, head.next, rev = rev, head, rev.next
        tail = tail.next
    return isPali
