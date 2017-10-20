//Remove Linked List Elements
//Remove all elements from a linked list of integers that have value val.
//Example
//Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
//Return: 1 --> 2 --> 3 --> 4 --> 5

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

//######################################### Recursion ######################################### 
public ListNode removeElements(ListNode head, int val) {
    if(head == null) return head;
    ListNode child = removeElements(head.next,val);
    if(head.val == val) return child;
    head.next = child;
    return head;
}
//################ Need to cleanup memory ################
ListNode* removeElements(ListNode* head, int val) {
    ListNode *dummy = new ListNode(1 - val);
    dummy->next = head;
    ListNode *prev = dummy;
    ListNode *tmp = head;
    while(tmp != NULL) {
        while(tmp != NULL && tmp->val == val) {
            tmp = tmp->next;
        }
        prev->next = tmp;
        prev = prev->next;
        if(tmp != NULL) { //[1],1
            tmp = tmp->next;
        }
    }
    return dummy->next;
}

//################### Recursive #################################
ListNode* removeElements(ListNode* head, int val) {
    if(head == NULL)  { 
      return NULL;
    }
    ListNode* next = removeElements(head->next, val);
    if(head->val == val) {
      return next;
    }
    head->next = next;
    return head;;
}

//################### Node clenup #################################
ListNode* removeElements(ListNode* head, int val) {
  ListNode** tmp = &head;
  ListNode* del = NULL;
  while(*tmp){
    if((*tmp)->val == val) {
      del = *tmp;
      *tmp = (*tmp)->next;
      delete del;
      del = NULL;
    }
    else { 
      tmp = &((*tmp)->next);
    }
  }
  return head;
}
