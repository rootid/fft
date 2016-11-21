//Given a binary tree, flatten it to a linked list in-place.
//For example,
//Given
//         1
//        / \
//       2   5
//      / \   \
//     3   4   6
//The flattened tree should look like:
//   1
//    \
//     2
//      \
//       3
//        \
//         4
//          \
//           5
//            \
//             6
//If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.
//
//
//
void flatten(TreeNode* root) {
    if(!root) {
        return;
    }
    TreeNode *tmp = root;
    TreeNode *prev_right = root->right;
    root->right = root->left;
    root->left = NULL;
    while(tmp->right != NULL) {
        tmp = tmp->right;
    }
    tmp->right = prev_right;
    flatten(root->right);
    return;
}
//Iterative approach
void flatten(TreeNode *root) {
        stack<TreeNode *> stk;
        if(root==NULL) 
           return;
        
        stk.push(root);
        TreeNode *oldptr=NULL;
        
        while(!stk.empty()){            // preorder traversal using a stack
            TreeNode *ptr=stk.top();    // Using ptr to do travesal 
            stk.pop();
            if(ptr->right) 
               stk.push(ptr->right);
            if(ptr->left) 
               stk.push(ptr->left);
            if(oldptr!=NULL){            // Using oldptr to change left and right pointer 
               oldptr->left=NULL;
               oldptr->right=ptr;
            }
            oldptr=ptr;
        }
       
}

int main() {
}
