
ListNode* mergeHelper(ListNode* f,ListNode *s) {
     ListNode *tmp = new ListNode(0);
     while(f || s) {
         if( s == NULL || f->val < s->val) {
             tmp->next = f;
             f = f->next;
         } else if(f == NULL || f->val > s->val) {
             tmp->next = s;
             s = s->next;
         }
     }
     return tmp->next;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
     if(lists.size()  == 0) {
         return NULL;
     }
     if(lists.size() == 1) {
         return lists[0];
     } 
     int sz = lists.size();
     int mid = sz/2;
     vector<ListNode *> fh(lists.begin(),lists.begin()+mid);
     vector<ListNode *> sh(lists.begin()+mid,lists.end());
     ListNode* t1 = mergeKLists(fh);
     ListNode* t2 = mergeKLists(sh);
     return mergeHelper(t1,t2);
 }
