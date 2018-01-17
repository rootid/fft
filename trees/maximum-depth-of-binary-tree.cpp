//Maximum Depth of Binary Tree
//Given a binary tree, find its maximum depth.
//The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
//


//######################################### Recursion  ######################################### 
public int maxDepth(TreeNode root) {
    if(root == null) return 0;
    if(root.left == null && root.right == null) return 1;
    return Math.max( maxDepth(root.left) , maxDepth(root.right)) + 1;
}

//######################################### Recursion  ######################################### 
int maxDepth(TreeNode* root) {

  if(!root) return 0;
  int ltHt = 1 + maxDepth(root->left);
  int rtHt = 1 + maxDepth(root->right);
  return max(ltHt,rtHt);

}
