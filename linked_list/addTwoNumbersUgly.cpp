//You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
//
//Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
//Output: 7 -> 0 -> 8
//

#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

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
