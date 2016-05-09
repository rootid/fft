//Lowest Common Ancestor of a Binary Search Tree
//
//Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
//According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
//        _______6______
//       /              \
//    ___2__          ___8__
//   /      \        /      \
//   0      _4       7       9
//         /  \
//         3   5
//For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

bool isFound(TreeNode *p,TreeNode *q) {
  if(!p) {
    return false;
  }
  if (p == q) {
    return true;
  } 
  bool l = isFound(p->left,q);
  bool r = isFound(p->right,q);
  return l || r ;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if(p->val < root->val && q->val < root->val) {
    root = lowestCommonAncestor(root->left,p,q);
  } else if(p->val > root->val && q->val > root->val) {
    root = lowestCommonAncestor(root->right,p,q);
  } 
  return root;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

  TreeNode *small = p;
  TreeNode *large = q;
  if(q->val < p->val) {
    small = q;
    large = p;
  }

  //can we reach to q from p if not then root is ancestor
  if ( true == isFound(small,large) ) {
    return small;
  }
  return root;
}
