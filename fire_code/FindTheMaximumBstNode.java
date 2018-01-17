
// Given a Binary Search Tree , return the node with the maximum data.
// Example:
//       4
//      / \                              
//     2   8
//        / \                     
//       5  10
// Output ==> 10

public class FindTheMaximumBstNode {
  // SC : O(1)
  public TreeNode findMaxI(TreeNode root) {
    if (root == null) {
      return null;
    }
    while (root.right != null) {
      root = root.right;
    }
    return root;
  }

  // SC : O(log n)
  public TreeNode findMaxR(TreeNode root) {
    if (root == null) {
      return null;
    }
    TreeNode node = findMax(root.right);
    return node == null ? root : node;
  }
}
