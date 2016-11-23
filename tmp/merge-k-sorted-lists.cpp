//Merge k Sorted Lists
//Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
//
//
//NOTE :  push_back, erase are time consuming,
//
//During 1st iteration, we merge two lists(every list is N) into one, this will make K down to K / 2.
//During 2nd iteration, we merge two lists(every list is 2N) into one, this will make K / 2 down to k /4.
//During 3rd iteration, we merge two lists(every list is 4N) into one, this will make K / 4 down to k /8.
//And so forth...
//I think when we merge two lists, the complexity is O(list1.length) + O(list2.length).
//So the total complexity is:
//(2N) * (K / 2) + 
//(4N) * (K / 4) + 
//(8N) * (K / 8) + 
//.............. + 
//(2^logK*N) * (K / (2 ^logK)) 
//= logK*KN
//
ListNode *mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == NULL ) return l2;
    else if (l2 == NULL ) return l1;
    if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
ListNode *mergeKLists(vector<ListNode *> &lists) {
    if (lists.empty()) return NULL;
    int len = lists.size();
    while (len > 1) {
        for (int i = 0; i < len / 2; ++i) {
            lists[i] = mergeTwoLists(lists[i], lists[len - 1 - i]);
        }
        len = (len + 1) / 2;
    }
    
    //return lists.front();
    return lists[0];
}
