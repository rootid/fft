//Given a sorted linked list, delete all duplicates such that each element appear only once.
//
//For example,
//Given 1->1->2, return 1->2.
//Given 1->1->2->3->3, return 1->2->3.


ListNode* deleteDuplicates(ListNode* head) {
    ListNode *tmp = head;
    while(tmp) {
        //if(tmp->next) {
           while(tmp->next && tmp->next->val == tmp->val) {
               tmp->next = tmp->next->next;
          // }   
        }
         tmp = tmp->next;
    }
    return head;
}


return h && (h->next = deleteDuplicates(h->next)) && h->next->val == h->val ? h->next : h;
Update after shawnyi's comment:

While the above does remove the duplicates from the list, it doesn't delete the nodes from memory, causing memory leaks. Here's a version which takes care of that.

if (h && (h->next = deleteDuplicates(h->next)) && h->next->val == h->val) delete h, h = h->next; return h;


ListNode* deleteDuplicates(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    ListNode* retHead = head;
    ListNode* first = head->next;
    while (first != NULL) {
        if (first->val != head->val) {
            head = head->next;
            head->val = first->val;
        }
        first = first->next;
    }
    
    // release nodes to avoid memory leak
    first = head->next;
    ListNode* delNode;
    while (first != NULL) {
        delNode = first;
        first = first->next;
        delete delNode;
    }
    
    head->next = NULL;
    
    return retHead;
}


int main() {

}
