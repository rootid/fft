import java.util.*;
// Given a binary tree consisting of nodes with positive integer values, write a
// method - maxSumPath that returns the maximum sum of data values obtained by
// traversing nodes along a path between any 2 nodes of the tree. The path must
// originate and terminate at 2 different nodes of the tree, and the maximum sum
// is obtained by summing all the data values of the nodes traversed along this
// path.
// Example:
//
//     1
//    / \
//   2   3     => 18
//  / \ / \
// 4  5 6  7
// Path: 5 -> 2 -> 1 -> 3 -> 7
// Max Sum = 5+2+1+3+7 = 18

public class MaximumSumPath {
  public static int maxSumPath(TreeNode root) {
    int[] res = new int[1];
    helper(root, res);
    return res[0];
  }

  public static int helper(TreeNode root, int[] res) {
    if (root == null) return 0;
    int l = helper(root.left, res);
    int r = helper(root.right, res);
    res[0] = Math.max(res[0], l + r + root.data);
    return Math.max(0, Math.max(l, r) + root.data);
  }
}
