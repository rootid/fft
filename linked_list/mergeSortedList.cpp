//Merge Two Sorted Lists
//Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists
#include "ll_header.h"
#include<iostream>

//Iterative Good
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

    if(l1 == NULL) { 
      return l2;
    }
    if(l2 == NULL) { 
      return l1;
    }
   ListNode *dummy = new ListNode(0);
   ListNode *l3 = dummy;
   while(l1 && l2) {
       if(l1->val < l2->val) {
            l3->next = l1;
            l1 = l1->next;
       } else {
           l3->next = l2;
           l2 = l2->next;
       }
       l3 = l3->next;
   } 
   if(l1) {
       l3->next = l1;
   }
   if(l2) {
       l3->next = l2;
   }
   return dummy->next;
}

//Iterative Ugly
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode *dummy = new ListNode(0);
    ListNode *l3 = dummy;
    while(l1 && l2) {
        if(l1->val < l2->val) {
             l3->next = l1;
             l1 = l1->next;
        } else if(l1->val > l2->val) {
            l3->next = l2;
            l2 = l2->next;
        } else {
            l3->next = l1;
            l1 = l1->next; // NOTE : after increment it worked else it failed
            l3 = l3->next;
            l3->next = l2;
            l2 = l2->next;
   
        }
        l3 = l3->next;
    } 
    while(l1) {
        l3->next = l1;
        l1 = l1->next;
        l3 = l3->next;
    }
    while(l2) {
        l3->next = l2;
        l2 = l2->next;
        l3 = l3->next;
    }
    l3->next = NULL;
    return dummy->next;
}
//Recursive 
//This solution is not a tail-recursive, the stack will overflow while the list is too long :)
//http://en.wikipedia.org/wiki/Tail_call
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
     if(l1 == NULL) return l2;
     if(l2 == NULL) return l1;
     
     if(l1->val < l2->val) {
         l1->next = mergeTwoLists(l1->next, l2);
         return l1;
     } else {
         l2->next = mergeTwoLists(l2->next, l1);
         return l2;
     }
 }
int main() {
  ListNode* l1 = new ListNode(1);
  ListNode* l2= new ListNode(1);
  mergeTwoLists(l1,l2);
}
