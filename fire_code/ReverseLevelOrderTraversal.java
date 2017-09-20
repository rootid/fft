// Reverse Level Order Traversal
// Traverse a given binary tree in the Reverse Level Order. Mark a node as
// visited by adding its data to an ArrayList which will be returned.
// Example:
//     1
//    / \
//   2   3
//  / \ / \
// 4  5 6  7
// Output => 4567231

public class ReverseLevelOrderTraversal {
  //###Iterative traversal###
  //## Modifed string reversal type example ###
  public ArrayList<Integer> levelorderRev(TreeNode root) {
    ArrayList<Integer> result = new ArrayList<>();
    if (root == null) return result;
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    while (!q.isEmpty()) {
      ArrayList<Integer> tmpList = new ArrayList<>();
      int nodeCount = q.size();
      for (int i = 0; i < nodeCount; ++i) {
        TreeNode tmp = q.poll();
        if (tmp.left != null) q.offer(tmp.left);
        if (tmp.right != null) q.offer(tmp.right);
        tmpList.add(tmp.data);
      }
      Collections.reverse(tmpList);
      for (int i : tmpList) result.add(i);
    }
    Collections.reverse(result);
    return result;
  }

  //###Iterative traversal with one traversal ###
  public ArrayList<Integer> levelorderRevOneReverse(final TreeNode root) {
    final ArrayList<Integer> result = new ArrayList<>();
    if (root == null) {
      return result;
    }
    final Queue<TreeNode> level = new LinkedList<>();
    level.add(root);
    while (!level.isEmpty()) {
      final TreeNode current = level.poll();
      if (current.right != null) {
        level.add(current.right);
      }
      if (current.left != null) {
        level.add(current.left);
      }
      result.add(current.data);
    }
    Collections.reverse(result);
    return result;
  }
}
