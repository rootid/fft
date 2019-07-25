//Merge Two Sorted Lists
//Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes
//of the first two lists

#include "../headers/global.hpp"
#include "../headers/listnode.hpp"


//######################################### Recursive #########################################
public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
    if(l1 == null) return l2;
    if(l2 == null) return l1;
    ListNode mergeHd = null;
    if(l1.val < l2.val) {
        mergeHd = l1;
        mergeHd.next = mergeTwoLists(l1.next, l2);
        return mergeHd;
    }
    mergeHd = l2;
    mergeHd.next = mergeTwoLists(l1, l2.next);
    return mergeHd;
}

//######################################### Recursive #########################################
public ListNode mergeTwoSortedList(ListNode l1, ListNode l2) {
    //base case
    if(l1 == null) return l2;
    if(l2 == null) return l1;

    //Recursion case - only modify the pointer
    if(l1.data < l2.data) {
        l1.next = mergeTwoSortedList(l1.next, l2);
        return l1;
    }
    l2.next = mergeTwoSortedList(l1, l2.next);
    return l2;
}

//######################################### Iterative #########################################
public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
     if(l1 == null) return l2;
     if(l2 == null) return l1;
     ListNode nextHead = new ListNode(42);
     ListNode tmpNode = nextHead;
     while(l1 != null || l2 != null) { //[1] []
         if(l2 == null ||  (l1 != null && l1.val < l2.val) )  {
             tmpNode.next = l1;
             l1 = l1.next;
         } else {
            tmpNode.next = l2;
            l2 = l2.next;
         }
         tmpNode = tmpNode.next;
     }
     tmpNode.next = null;
     return nextHead.next;
}


namespace good {

//######################################### Iteration  #########################################
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
//#########################################Recursive #########################################
//This solution is not a tail-recursive, the stack will overflow while the list is too long :)
//http://en.wikipedia.org/wiki/Tail_call
namespace recursive {
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
}


//######################################### Merge2Lists #########################################
//If both lists are non-empty, I first make sure a starts smaller, use its head as result, and merge the remainders
//behind it. Otherwise, i.e., if one or both are empty, I just return what's there.
class Solution:
    def mergeTwoLists(self, a, b):
        if a and b:
            if a.val > b.val:
                a, b = b, a
            a.next = self.mergeTwoLists(a.next, b)
        return a or b
//######################################### Return b  #########################################
//First make sure that a is the "better" one (meaning b is None or has larger/equal value).
//Then merge the remainders behind a.
def mergeTwoLists(self, a, b):
    if not a or b and a.val > b.val:
        a, b = b, a
    if a:
        a.next = self.mergeTwoLists(a.next, b)
    return a

int main() {
  ListNode* l1 = new ListNode(1);
  ListNode* l2= new ListNode(1);
  mergeTwoLists(l1,l2);
}
/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
