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

//NOTE : To avoid memory leak 
//ListNode sentinel(0);
//ListNode *curr = &sentinel;
//return sentinel.next;

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

int main() {
}
