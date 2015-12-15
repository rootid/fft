#invert binary tree



TreeNode* invertBT (TreeNode *root) {

  if (!root) {
    return root;
  }
  TreeNode *tmp = invertBT (root->left);
  root->right = tmp;
  invertBT (root->right);
  return root;
}
