

boolean validateBST(TreeNode root) {
  return helper(root, null);
}

//Inorder traversal op increasing order
boolean helper(TreeNode root, TreeNode prev) {
  boolean isBST = true;
  if(!root) {
    return isBST;
  }
  if(root.left) {
   isBST = helper(root, root.left);
  }
  if( !isBST || root.value <prev.value) {
    return false;
  }
  helper(root.right, root);
}
