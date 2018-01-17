//Balanced Binary Tree
//Given a binary tree, determine if it is height-balanced.
//For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

//O(N)
int dfsHeight (TreeNode *root) {
    if (root == NULL) return 0;
    int leftHeight = dfsHeight (root -> left);
    if (leftHeight == -1) return -1;
    int rightHeight = dfsHeight (root -> right);
    if (rightHeight == -1) return -1;
    
    if (abs(leftHeight - rightHeight) > 1)  return -1;
    return max (leftHeight, rightHeight) + 1;
}
bool isBalanced(TreeNode *root) {
    return dfsHeight (root) != -1;
}


// for each level you are doing a total scan of N, and there are logN levels  O(NlogN)
int getDepth(TreeNode *root) {
  int l = 0;
  int r = 0;
  
  if(!root) {
    return 0;
  } 
  if(root->left) {
    l = getDepth(root->left);
  }
  if (root->right) {
    r = getDepth(root->right);
  }
  return max(l,r) + 1;
}

bool isBalanced(TreeNode* root) {
  if(!root) {
    return true;
  }
  if( abs( getDepth (root->left) - getDepth(root->right) ) <= 1 ) {
     bool l = isBalanced(root->left);
     bool r = isBalanced(root->right);
     return l && r;
  }  else {
      return false;
  }
}
