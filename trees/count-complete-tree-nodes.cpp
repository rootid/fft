//Given a complete binary tree, count the number of nodes.
//Definition of a complete binary tree from Wikipedia:
//In a complete binary tree every level, except possibly the last, is
//completely filled, and all nodes in the last level are as far left as
//possible. It can have between 1 and 2h nodes inclusive at the last level h.
//
//O(n)
int countNodes(TreeNode* root) {
     if(!root) {
         return 0;
     }
     return 1 + countNodes(root->left) + countNodes(root->right);
}
//O(log(n)^2)
//
int getHeight(TreeNode *root) {
  if(!root) {
    return -1;
  }
  return 1+ getHeight(root->left);
}

int countNodes(TreeNode* root) {
  int h = getHeight(root);

  if(h < 0) {
      return 0;
  }
  if ( getHeight(root->right) == h-1 ) {
    // right subtree and the left subtree is a full tree of height h-1
    // last node on the last tree row is in the right subtree
    return (1 << h) + countNodes(root->right);
  }
  // right subtree and the left subtree is a full tree of height h-2
  // last node on the last tree row is in the left subtree
  return (1 << h-1) + countNodes(root->left);
}

int countNodes(TreeNode* root) {
    int nodes = 0, h = getHeight(root);
    while (root != NULL) {
        if (getHeight(root->right) == h - 1) {
            nodes += 1 << h;
            root = root->right;
        } else {
            nodes += 1 << h-1;
            root = root->left;
        }
        h--;
    }
    return nodes;
}
