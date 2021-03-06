//Add Two Numbers II
//You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes
//first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
//You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//Follow up:
//What if you cannot modify the input lists? In other words, reversing the lists is not allowed.
//Example:
//Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
//Output: 7 -> 8 -> 0 -> 7
#include "../headers/global.hpp"
#include "../headers/listnode.hpp"

//############################## With Stack + Carry and Dummy Node##############################
public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    ListNode nHd = null;
    Deque<ListNode> l1Stk = new ArrayDeque<>();
    Deque<ListNode> l2Stk = new ArrayDeque<>();
    while(l1 != null) {
        l1Stk.push(l1);
        l1 = l1.next;
    }
    while(l2 != null) {
        l2Stk.push(l2);
        l2 = l2.next;
    }
    int carry = 0;

    while(!l1Stk.isEmpty() || !l2Stk.isEmpty()) {
        if(!l1Stk.isEmpty()) carry += l1Stk.pop().val;
        if(!l2Stk.isEmpty()) carry += l2Stk.pop().val;
        //Prepend the result
        ListNode preNode = new ListNode(carry%10);
        preNode.next = nHd;
        nHd = preNode;
        carry = carry/10;
    }
    if(carry == 1) {
        ListNode carryNode = new ListNode(1);
        carryNode.next = nHd;
        return carryNode;
    }
    return nHd;
}


//############################## With Stack + Carry and Dummy Node##############################
public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    if(l1 == null) return l2;
    if(l2 == null) return l1;
    Deque<ListNode> stk1 = new ArrayDeque<>();
    Deque<ListNode> stk2 = new ArrayDeque<>();
    ListNode dummyNode = new ListNode(0);
    int sum = 0;
    while(l1 != null || l2 != null) {
        if(l1 != null) {
            stk1.push(l1);
            l1 = l1.next;
        }
        if(l2 != null) {
            stk2.push(l2);
            l2 = l2.next;
        }
    }
    while(!stk1.isEmpty() || !stk2.isEmpty()) {
        if(!stk1.isEmpty()) sum += stk1.pop().val;
        if(!stk2.isEmpty()) sum += stk2.pop().val;
        dummyNode.val = sum % 10;
        ListNode carryNode = new ListNode(sum/10);
        carryNode.next = dummyNode;
        dummyNode = carryNode;
        sum /= 10;
    }
    return dummyNode.val == 0 ? dummyNode.next : dummyNode;
}


//############################## With Stack ##############################
 public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
     if(l1 == null) return l2;
     if(l2 == null) return l1;
     Deque<ListNode> stk1 = new ArrayDeque<>();
     Deque<ListNode> stk2 = new ArrayDeque<>();
     ListNode head = null;
     int sum = 0;
     while(l1 != null || l2 != null) {
         if(l1 != null) {
             stk1.push(l1);
             l1 = l1.next;
         }
         if(l2 != null) {
             stk2.push(l2);
             l2 = l2.next;
         }
     }
     while(!stk1.isEmpty() || !stk2.isEmpty()) {
         if(!stk1.isEmpty()) sum += stk1.pop().val;
         if(!stk2.isEmpty()) sum += stk2.pop().val;
         ListNode tmp = new ListNode(sum%10);
         tmp.next = head;
         head = tmp;
         sum /= 10;
     }
     if(sum >= 1) {
         ListNode tmp = new ListNode(sum);
         tmp.next = head;
         head = tmp;
     }
     return head;
 }

//############################## With Stack ##############################
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
       stack<int> st1; // store l1
       stack<int> st2; // store l2
       ListNode* prev = NULL;//= new ListNode(-1);
       ListNode* head;
       int sum = 0;

       // push l1's elements into stack
       while(l1) {
           st1.push(l1->val);
           l1 = l1->next;
       }

       // push l2's element into stack
       while(l2) {
           st2.push(l2->val);
           l2 = l2->next;
       }

       // calculate
       while(!st1.empty() || !st2.empty()) {
           sum /= 10;
           if(!st1.empty()) {
               sum += st1.top();
               st1.pop();
           }

           if(!st2.empty()) {
               sum += st2.top();
               st2.pop();
           }

           head = new ListNode(sum % 10);
           head->next = prev;
           prev = head;
       }

       // check whether there is carry bit
       if(sum >= 10) {
           head = new ListNode(sum / 10);
           head->next = prev;
       }

       return head;
}


//############################## W/O Stack ##############################
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int n1 = getLength(l1), n2 = getLength(l2), diff = abs(n1 - n2);
    if (n1 < n2) swap(l1, l2); //|l1| > |l2|
    ListNode *dummy = new ListNode(0), *cur = dummy, *right = cur;
    while (diff > 0) {
        cur->next = new ListNode(l1->val);
        if (l1->val != 9) right = cur->next;
        cur = cur->next;
        l1 = l1->next;
        --diff;
    }
    while (l1) {
        int val = l1->val + l2->val;
        if (val > 9) {
            val %= 10;
            ++right->val;
            while (right->next) {
                right->next->val = 0;
                right = right->next;
            }
            right = cur;
        }
        cur->next = new ListNode(val);
        if (val != 9) right = cur->next;
        cur = cur->next;
        l1 = l1->next;
        l2 = l2->next;
    }
    return (dummy->val == 1) ? dummy : dummy->next;
}
int getLength(ListNode* head) {
    int cnt = 0;
    while (head) {
        ++cnt;
        head = head->next;
    }
    return cnt;
}

// vim: set sw=2 sts=2 tw=120 et nospell :
