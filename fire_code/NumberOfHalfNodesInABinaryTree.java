// Write a function to find the total number of half nodes in a binary tree. A
// half node is a node which has exactly one child node. If there are no half
// nodes, return 0.
// Example:
//       1
//      / \
//     2   3
//    / \ / \
//   4  5 6  7
//  /
// 8
//
// Half nodes count => 1

public class NumberOfHalfNodesInABinaryTree {
  //########### Good ###########
  public int numberOfHalfNodes(TreeNode root) {
    if (root == null) return 0;
    int self = 0;
    if (root.left == null ^ root.right == null)  // xor
      self = 1;
    return self + numberOfHalfNodes(root.left) + numberOfHalfNodes(root.right);
  }

  //########### Ugly ###########
  public int numberOfHalfNodesUgly(TreeNode root) {
    if (root == null) return 0;
    if (root.left != null && root.right == null)
      return 1 + numberOfHalfNodes(root.left);
    if (root.left == null && root.right != null)
      return 1 + numberOfHalfNodes(root.right);
    int left = numberOfHalfNodes(root.left);
    int right = numberOfHalfNodes(root.right);
    return left + right;
  }
}
