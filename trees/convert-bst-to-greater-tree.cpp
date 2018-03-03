//Convert BST to Greater Tree
//Given a Binary Search Tree (BST), convert it to a Greater Tree such that
//every key of the original BST is changed to the original key plus sum of all
//keys greater than the original key in BST.
//Example:
//Input: The root of a Binary Search Tree like this:
//              5
//            /   \
//           2     13
//Output: The root of a Greater Tree like this:
//             18
//            /   \
//          20     13

//############################# Traverse from right to left in DFS way with adding the root->val  #############################
void helper(TreeNode* root,int& sum) {
  if (root) {
    helper(root->right,sum);
    root->val += sum;
    sum = root->val;
    helper(root->left,sum);
  }
}

TreeNode* convertBST(TreeNode* root) {
  int sum = 0;
  helper(root,sum);
  return root;
}


//############################# Iterative version #############################
TreeNode* convertBST(TreeNode* root) {
    if(root == nullptr) return root;
    auto root2 = root;
    vector<TreeNode*> vec;
    stack<TreeNode*> sk;
    int sum = 0;
    while(true){ //3->9->15 , 1<-3->9->15
        while(root){
            sk.push(root);
            root = root->left;
        }
        if(sk.empty()) break;
        auto tmp = sk.top();
        sum += tmp->val;
        sk.pop();
        vec.push_back(tmp);
        root = tmp->right;
    }
    for(auto node : vec){
        sum -= node->val;
        node->val += sum;
    }
    return root2;
}
//##########################################  Morris traversal ###############################################################

TreeNode* convertBST(TreeNode* root) {
       TreeNode* cur= root;
       int sum = 0;
       while (cur != null) {
           if (cur->right == null) {
               int tmp = cur->val;
               cur->val += sum;
               sum += tmp;
               cur = cur->left;
           } else {
               TreeNode* prev = cur->right;
               while (prev->left != null || prev->left != cur)
                   prev = prev->left;
               if (prev->left == null) {
                   prev->left = cur;
                   cur = cur->right;
               } else {
                   prev->left = null;
                   int tmp = cur->val;
                   cur->val += sum;
                   sum += tmp;
                   cur = cur->left;
               }
           }
       }
       return root;
   }
