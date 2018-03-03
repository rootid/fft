//Diameter of Binary Tree
//Given a binary tree, you need to compute the length of the diameter of the
//tree. The diameter of a binary tree is the length of the longest path between
//any two nodes in a tree. This path may or may not pass through the root.
//Example:
//Given a binary tree
//          1
//         / \
//        2   3
//       / \
//      4   5
//Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
//Note: The length of path between two nodes is represented by the number of
//edges between them.

//################################################ Postorder traversal ################################################
int diameterOfBinaryTree(TreeNode* root) {
  int maxHt = 0;
  helper(root,maxHt);
  return maxHt;
}

int helper(TreeNode* root,int &maxHt){
  if(root == nullptr)
    return 0;
  int left = helper(root->left,maxHt) + (root->left == nullptr ? 0 : 1);
  int right = helper(root->right,maxHt) + (root->right == nullptr ? 0 : 1);
  maxHt = max(left + right,maxHt); //update the maxHt
  return max(left,right); //choose the max between left and right substree
}

//################################################ Postorder traversal with memory ################################################
int diameterOfBinaryTree(TreeNode* root) {
    return depthDiameterOfBinaryTree(root).second;
}

pair<int, int> depthDiameterOfBinaryTree(TreeNode* root) {
    if (!root) return pair<int, int> (0, 0);
    pair<int, int> left = depthDiameterOfBinaryTree(root->left);
    pair<int, int> right = depthDiameterOfBinaryTree(root->right);
    return pair<int, int> (1 + max(left.first, right.first), max(max(left.second, right.second), left.first + right.first));
}

//################################################ Postorder traversal ################################################
//postorder(LRD) traversal so that we can get O(n) if it is preorder(DLR) it
//will be O(n^2)
int height(TreeNode* root) {
    if(root==NULL) return 0;
    if(root->left == NULL and root->right == NULL) return 1;
    return max(height(root->left),height(root->right))+1;
}
void dfs(TreeNode* root, int &res) {
    if(root == NULL) return ;
    dfs(root->left,res);
    dfs(root->right,res);
    res = max(res, height(root->left) + height(root->right));
}
int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;;
    dfs(root,res);
    return res;
}

