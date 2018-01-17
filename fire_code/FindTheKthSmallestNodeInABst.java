// Find the kth Smallest Node in a BST
// Given a binary search tree and an integer k, implement a method to find and
// return the kth smallest node.
// Example:
//       4
//      / \                              
//     2   8
//        / \                     
//       5  10
// K = 2, Output = 4

public class FindTheKthSmallestNodeInABst {
  public TreeNode findKthSmallest(TreeNode root, int k) {
    if (root == null) {
      return root;
    }
    int left =
        nodeCount(root.left);  // this value can be saved in the root node
    if (left + 1 == k) {
      return root;
    } else if (left + 1 < k) {
      return findKthSmallest(root.right, k - left - 1);
    }
    return findKthSmallest(root.left, k);
  }
  private int nodeCount(TreeNode root) {
    if (root == null) {
      return 0;
    }
    return 1 + nodeCount(root.left) + nodeCount(root.right);
  }
}
