//Sort a linked list using insertion sort.

///################## with array
void insertionSort(int a[],int len) {
    for (int i=0;i<len;i++) {
        for (int j=i;j>0;j--) {
            if (a[j] < a[j-1]) {
                swap(a[j],a[j-1]);
            } else {
                break;
            }
        }
    }
}

///################## with Node ################## 
ListNode* insertionSortList(ListNode* head) {
        if (!head) return NULL;
   ListNode *dummy = new ListNode(0), *outer = head;
   dummy->next = head;
   while (outer && outer->next) {
       ListNode *inner = dummy, *temp = NULL;
       while (inner != outer) {
           if (inner->next->val > outer->next->val) {    // find right place to insert
               temp = inner->next;
               inner->next = outer->next;
               outer->next = outer->next->next;
               inner->next->next = temp;
               break;
           }
           inner = inner->next;
       }
       if (inner == outer) outer = outer->next;
   }
   return dummy->next;
}

///################## with Node ################## 
ListNode *insertionSortList(ListNode *head) {
    ListNode* dummy = new ListNode(INT_MIN);
    ListNode* now = head;
    ListNode* pre = nullptr;
    while (now != nullptr) {
        pre = dummy;
        while (pre->next != nullptr && pre->next->val < now->val) {
            pre = pre->next;
        }
        ListNode* preNext = pre->next;
        ListNode* nowNext = now->next;
        pre->next = now;
        now->next = preNext;
        now = nowNext;
    }
    return dummy->next;
}

///################## with Node ################## 
ListNode *insertionSortList(ListNode *head) {
        ListNode* res = new ListNode(-1);
        ListNode* cur = res;
        //head is the current node we are dealing with
        while (head) {
            ListNode *next = head->next;
            cur = res;
            while (cur->next && cur->next->val <= head->val) {
                cur = cur->next;
            }
            //insert the head node into the list
            head->next = cur->next;
            cur->next = head;
            //move forward the head node
            head = next;
        }
        return res->next;
}
