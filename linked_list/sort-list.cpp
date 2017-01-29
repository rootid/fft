//Sort List
//Sort a linked list in O(n log n) time using constant space complexity.

//################################################################## GOOD ################################################################## 
ListNode *merge(ListNode *list1,ListNode *list2){
     ListNode *head;
     ListNode **p=&head,**q;
     while (list1 || list2){
         if (list1 && list2)  { 
           q = list1->val < list2->val? &list1: &list2;
         } else { 
           q = list1 ? &list1:&list2;
         }
         *p=*q;
         *q=(*q)->next;
         p=&((*p)->next);
     }
     return head;
}
ListNode* sortList(ListNode* head) {
     if (!head || !head->next) return head;
     //find middle
     ListNode *slow=head,*fast=head->next;
     while (fast && fast->next){
         slow=slow->next;
         fast=fast->next->next;
     }
     fast=slow->next;
     slow->next=NULL;
     return merge(sortList(head),sortList(fast));
}

//################################################################## GOOD ################################################################## 
ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == NULL)
        return head;
    ListNode *fast = head->next->next, *slow = head;
    while(fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    ListNode *r = sortList(slow->next);
    slow->next = NULL;
    ListNode *l = sortList(head);
    return merge(l, r);
}

ListNode *merge(ListNode *l, ListNode *r) {
    ListNode *dummy = new ListNode(0), *node;
    node = dummy;
    while (l && r) {
        if (l->val < r->val) {
            node->next = l;
            l = l->next;
        } else {
            node->next = r;
            r = r->next;
        }
        node = node->next;
    }
    if (l)
        node->next = l;
    else 
        node->next = r;

    ListNode *tmp = dummy->next;
    delete(dummy);
    return tmp;
    //return dummy->next;
}


//################################################################## GOOD ################################################################## 
ListNode* sortList(ListNode* head) {
ListNode* sortList(ListNode* head) {
     if (head == NULL || head->next == NULL) {
         return head;
     }
     ListNode* slow = head;
     ListNode* fast = head->next;
     while (fast != NULL && fast->next != NULL) {
         slow = slow->next;
         fast = fast->next->next;
     }
     //divide the list into two parts 
     fast = slow->next;
     slow->next = NULL;
     return merge(sortList(head), sortList(fast));
}
    
ListNode* merge(ListNode* l1, ListNode* l2) {
    ListNode dump(0);
    ListNode* cur = &dump;
    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        }
        else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    if (l1 != NULL)
        cur->next = l1;
    else
        cur->next = l2;
        
    return dump.next;
}
//Actually you are sorting them when you merge the two lists,as the following:
//3->8->12->null (must be sorted)
//1->10->23->null
//after merging:
//1->3->8->10->12->23->null.
//Of course the two lists must are ordered respectively.So we can only start to merge two lists that only 
//have one element,then we get a ordered list that have two element,do this again (that is "recursion").
// 7 -> 3 -> 9 -> 6 -> 2 -> 8 -> 4 -> 1 -> null
//  \ /       \ /       \ /        \ /
//3->7->null 6->9->null 2->8->null 1->4->null
//    \     /              \      /
//3->6->7->9->null  1->2->4->8->null
//     \               /
//1->2->3->4->6->7->8->9->null
