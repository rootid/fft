import java.util.*;

// Find the Sum of all Elements in a Binary Tree Iteratively
// Given a binary tree, write a method to find and return the sum of all nodes
// of the tree iteratively.
// Example:
//       1
//      / \
//     2   3
//    / \ / \        
//   4  5 6  7
//  /
// 8
//  ==> sum of all nodes = 36
//  (1+2+3+4+5+6+7+8)

public class FindTheSumOfAllElementsInABinaryTreeIteratively {
  public int sumItr(TreeNode root) {
    if (root == null) {
      return 0;
    }
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    int sum = 0;
    while (!q.isEmpty()) {
      TreeNode curr = q.poll();
      sum += curr.data;
      if (curr.left != null) q.offer(curr.left);
      if (curr.right != null) q.offer(curr.right);
    }
    return sum;
  }
}
