//Add Two Numbers
//You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
//
//Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
//Output: 7 -> 0 -> 8
//

//NOTE : To avoid memory leak
//ListNode sentinel(0);
//ListNode *curr = &sentinel;
//return sentinel.next;

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"


//##################################################### Recursion GOOD  #####################################################
public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    return addTwoNumbersHelper(l1,l2);
}

 private ListNode addTwoNumbersHelper(ListNode l1, ListNode l2) {
    if(l1 == null && l2 == null) return l1;
    if(l1 == null) return l2;
    if(l2 == null) return l1;
    int carry = l1.val + l2.val;
    ListNode head = new ListNode(carry % 10);
    head.next = addTwoNumbersHelper(l1.next, l2.next);
    if(carry >= 10) { //max sum = 18 [9+9]
        head.next = addTwoNumbersHelper(head.next, new ListNode(1));
    }
    return head;
 }


//##################################################### Recursion GOOD  #####################################################
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == NULL and l2 == NULL) return NULL;
    else if (l1 == NULL) return l2;
    else if (l2 == NULL) return l1;
    int carry  = l1->val + l2->val;
    ListNode *p = new ListNode(carry % 10);
    p->next = addTwoNumbers(l1->next,l2->next);
    if (carry >= 10)  {
        p->next = addTwoNumbers(p->next, new ListNode(1));
    }
    return p;
}

//##################################################### GOOD #####################################################
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  ListNode *sentinel = new ListNode(0);
  ListNode *tmp = sentinel;
  bool isCarry = false;
  int carry = 0;
  while(l1 || l2 || carry) {

    if(l1) {
       carry += l1->val;
       l1 = l1->next;
    }
    if(l2) {
       carry += l2->val;
       l2 = l2->next;
    }
    tmp->next = new ListNode(carry % 10);
    carry = carry / 10;
    tmp = tmp->next;
  }
  return sentinel->next;
}

//##################################################### UGLY #####################################################
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
       ListNode *sumHeadNode = new ListNode(0);
       ListNode *tmp = sumHeadNode;
       bool isCarry = false;
       int carry = 0;
       while(l1 && l2) {
           tmp->next = new ListNode(0);
           tmp = tmp->next;
           if(isCarry == true) {
              tmp->val = (l1->val + l2->val + 1) % 10;
              carry = (l1->val + l2->val + 1) / 10;
           } else {
              tmp->val = (l1->val + l2->val) % 10;
              carry = (l1->val + l2->val) / 10;
           }
           if (carry > 0) {
               isCarry = true;
           } else {
               isCarry = false;
           }
           l1 = l1->next;
           l2 = l2->next;
       }
       while(l1) {
           tmp->next = new ListNode(0);
           tmp = tmp->next;
           if(isCarry == true) {
              tmp->val = (l1->val  + 1) % 10;
              carry = (l1->val + 1) / 10;
           } else {
              tmp->val = (l1->val ) % 10;
              carry = (l1->val) / 10;
           }
           if (carry > 0) {
               isCarry = true;
           } else {
               isCarry = false;
           }
           l1 = l1->next;
       }
       while(l2) {
              tmp->next = new ListNode(0);
              tmp = tmp->next;
            if(isCarry == true) {
              tmp->val = (l2->val + 1) % 10;
              carry = (l2->val + 1) / 10;
           } else {
              tmp->val = (l2->val) % 10;
              carry = (l2->val) / 10;
           }
           if (carry > 0) {
               isCarry = true;
           } else {
               isCarry = false;
           }
           l2 = l2->next;
       }
       if(isCarry == true) {
          tmp->next = new ListNode(0);
          tmp = tmp->next;
          tmp->val = carry;
       }
    return sumHeadNode->next;
}


int main() {
}

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
