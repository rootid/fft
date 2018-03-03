//Recover Binary Search Tree
//Two elements of a binary search tree (BST) are swapped by mistake.
//Recover the tree without changing its structure.
//Note:
//A solution using O(n) space is pretty straight forward. Could you devise a
//constant space solution?
//############################### Recursion + inorder + space O(log n) ###############################
void dfsDetectSwap(TreeNode* root,TreeNode*& prev,TreeNode*& first,TreeNode*& second){
    if(root==NULL)  return;
    dfsDetectSwap(root->left,prev,first,second);
    if(first== nullptr && prev->val >= root->val) {
      first=prev;
    }
    if(first!=NULL && prev->val >= root->val) {
      second=root;
    }
    prev=root;
    dfsDetectSwap(root->right,prev,first,second);
}
void recoverTree(TreeNode* root) {
  TreeNode* first = nullptr;
  TreeNode* second = nullptr;
  TreeNode* prev = new TreeNode(INT_MIN);
  dfsDetectSwap(root,prev,first,second);
  swap(first->val, second->val);
}
//############################### Morris + inorder + space O(1) ###############################
//
 void recoverTree(struct TreeNode* root) {
   TreeNode *pre=NULL, *first=NULL, *second=NULL;
   while(root) {
     if(root->left == NULL) {
       if(pre && pre->val > root->val) {
         if(!first) first = pre;
         second = root;
       }
       pre = root;
       root = root->right;
     } else {
       TreeNode *t = root->left;
       while(t->right && t->right!=root) t = t->right;
       if(!t->right) {
           t->right = root;
           root = root->left;
       } else {
           t->right = NULL;
           if(pre && pre->val > root->val) {
               if(!first) first = pre;
               second = root;
           }
           pre = root;
           root = root->right;
       }
     }
   }
   if(first && second)
     swap(first->val, second->val);
}

//##################### Morris traversal modifies tree  O(1) traveresal #####################
//connects right subtree to root
void inorderMorrisTraversal(TreeNode *root) {
    TreeNode *cur = root, *prev = NULL;
    while (cur != NULL) {
        if (cur->left == NULL) { //1.
            cout << cur->val << endl;
            cur = cur->right;
        } else {
            // find predecessor
            prev = cur->left;
            while (prev->right != NULL && prev->right != cur) {
                prev = prev->right;
            }
            if (prev->right == NULL) { // 2.a) node connect
                prev->right = cur; //5->6
                cur = cur->left; //visit next left subtree node
            } else { // 2.a)
                prev->right = NULL;
                printf("%d ", cur->val);
                cur = cur->right;
            }
        }
    }
}
