import java.util.*;
// Given a binary tree, write a method to perform a levelorder traversal and
// return an ArrayList of integers containing the data of the visited nodes in
// the correct order.
// Example:
//     1
//    / \
//   2   3     ==> 1234567
//  / \ / \
// 4  5 6  7

public class LevelorderTraversal {
  public ArrayList<Integer> levelorder(TreeNode root) {
    ArrayList<Integer> resultList = new ArrayList<>();
    if (root == null) return resultList;
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    while (!q.isEmpty()) {
      TreeNode tmp = q.poll();
      resultList.add(tmp.data);
      if (tmp.left != null) q.offer(tmp.left);
      if (tmp.right != null) q.offer(tmp.right);
    }
    return resultList;
  }
}
