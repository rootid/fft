//Given a singly linked list where elements are sorted in ascending order,
//convert it to a height balanced BST.
//1
//1->2
//1->2->3


TreeNode *sl_bst_helper(ListNode *head,ListNode *tail) {
     if(head == tail) {
         return NULL;
     }
     ListNode *fast = head;
     ListNode *slow = head;
     while(fast != tail && fast->next != tail) {
           fast = fast->next->next;
           slow = slow->next;
     }
     TreeNode *root = new  TreeNode(slow->val);
     root->left = sl_bst_helper(head,slow);
     root->right = sl_bst_helper(slow->next,tail);
     return root;
}

TreeNode* sortedListToBST(ListNode* head) {
     return sl_bst_helper(head,NULL);
}
