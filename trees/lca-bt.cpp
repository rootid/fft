//Lowest Common Ancestor of a Binary Tree
//Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
//According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
//        _______3______
//       /              \
//    ___5__          ___1__
//   /      \        /      \
//   6      _2       0       8
//         /  \
//         7   4
//For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if(!root || p == root || q == root) {
    return root;
  }
  TreeNode *left = lowestCommonAncestor(root->left,p,q);
  TreeNode *right = lowestCommonAncestor(root->right,p,q);
  if(left != NULL && right != NULL) {
    return root;
  }
  if(right == NULL) {
    return left;
  }
  return right;
 //return !left ? right : !right ? left : root;
 //if(left == NULL) {
 //  return right;
 //}
 //if(right == NULL) {
 //  return left;
 //}
 //return root;
 //
 //
 //if(!root) {
 //       return NULL;
 //   }
 //   if(p == root || q == root) {
 //       return root;
 //   }
 //   
 //   TreeNode *left = lowestCommonAncestor(root->left,p,q);
 //   TreeNode *right = lowestCommonAncestor(root->right,p,q);
 //   if(left == NULL) {
 //       return right;
 //   } 
 //   if(right == NULL) {
 //       return left;
 //   }
 //   return root;
        
}
//this might go into each subtree twice. Which means you might go into each subsubtree four times. And into each subsubsubtree eight times. And so on. That takes exponential time, which is very slow.
//
//def lowestCommonAncestor(self, root, p, q):
//    if not root or p == root or q == root:
//        return root
//    if self.lowestCommonAncestor(root.left, p, q) and self.lowestCommonAncestor(root.right, p, q):
//        return root
//    return self.lowestCommonAncestor(root.left, p, q) or self.lowestCommonAncestor(root.right, p, q)
