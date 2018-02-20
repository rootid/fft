//Given a linked list, swap every two adjacent nodes and return its head.
//For example,
//Given 1->2->3->4, you should return the list as 2->1->4->3.
//Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.


//############################### Recursion  ###############################
//Same trik as reverse linked list nk....>nk+1
public ListNode swapPairs(ListNode head) {
     if (head == null || head.next == null) return head;
     ListNode grandChild = swapPairs(head.next.next); //head-> (head->next) -> (head->next->next)
     ListNode child = head.next;                       //head->child
     child.next = head;                                 //child->head
     head.next = grandChild;                            //child->head->grandChild
     return child;
}


//############################### Recursion  ###############################
  public ListNode swapPairs(ListNode head) {
        if ((head == null)||(head.next == null))
            return head;
        ListNode n = head.next;
        head.next = swapPairs(head.next.next);
        n.next = head;
        return n;
    }

//############################### Iteration ###############################

public ListNode swapPairs(ListNode head) {
        if (head == null || head.next == null) return head;
        ListNode cur = head;
        ListNode newHead = head.next;
        while (cur != null && cur.next != null) {
            ListNode tmp = cur;
            cur = cur.next;
            tmp.next = cur.next;
            cur.next = tmp;
            cur = tmp.next;
            if (cur != null && cur.next != null) tmp.next = cur.next;
        }
        return newHead;
    }


//############################### Iteration ###############################
ListNode* swapPairs(ListNode* head) {
    ListNode **pp = &head, *a, *b;
    while ((a = *pp) && (b = a->next)) {
        a->next = b->next;
        b->next = a;
        *pp = b;
        pp = &(a->next);
    }
    return head;
}

//###############################  Recursion ###############################
ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode *grandChild = swapPairs(head->next->next); //head-> (head->next) -> (head->next->next)
        ListNode *child = head->next;                       //head->child
        child->next = head;                                 //child->head
        head->next = grandChild;                            //child->head->grandChild
        return child;
}

ListNode* swapPairs(ListNode* head) {
    ListNode **pp = &head, *a, *b;
    while ((a = *pp) && (b = a->next)) {
        a->next = b->next;
        b->next = a;
        *pp = b;
        pp = &(a->next);
    }
    return head;
}



/*
       #---->@---->@---->@---->@---->@---->@
                   ^     ^
                   pre   cur

      1. pre->next = cur->next
                    __________
                   /          \
       #---->@---->@     @---->@---->@---->@
                   ^     ^
                   pre   cur

      2. pre = pre->next
                    __________
                   /          \
      #---->@---->@      @---->@---->@---->@
                         ^     ^
                         cur   pre

      3. cur->next = pre->next
                    __________
                   /          \
       #---->@---->@     @     @---->@---->@
                          \_________/
                         ^     ^
                         cur   pre

      4. pre->next = cur
                   __________
                  /          \
      #---->@---->@     @<----@     @---->@
                         \_________/
                        ^     ^
                        cur   pre

      5. pre = cur; cur = cur->next
                   __________
                  /          \
      #---->@---->@     @<----@     @---->@
                         \_________/
                        ^           ^
                        pre         cur
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head) return NULL;
        ListNode tmp(0);
        tmp.next = head;
        ListNode *pre = &tmp, *cur = head;
        while(cur && cur->next){
            pre->next = cur->next;
            pre = pre->next;
            cur->next = pre->next;
            pre->next = cur;
            pre = cur;
            cur = cur->next;
        }
        return tmp.next;
    }
}
/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
