//Count Univalue Subtrees
//Given a binary tree, count the number of uni-value subtrees.
//A Uni-value subtree means all nodes of the subtree have the same value.
//For example:
//Given binary tree,
//              5
//             / \
//            1   5
//           / \   \
//          5   5   5
//return 4.
//
//
//Helper all tells whether all nodes in the given tree have the given value. And while doing that,
//it also counts the uni-value subtrees.
//######################################### Recursion #########################################
class Solution {
  int count = 0;
  boolean all(TreeNode root, int val) {
      if (root == null)
          return true;
      if (!all(root.left, root.val) | !all(root.right, root.val))
          return false;
      count++;
      return root.val == val;
  }
  public int countUnivalSubtrees(TreeNode root) {
      all(root, 0);
      return count;
  }
}


//######################################### Recursion #########################################
class Solution {
  int count = 0;
  boolean all(TreeNode root, int val) {
      if (root == null)
          return true;
      if (!all(root.left, root.val) | !all(root.right, root.val))
          return false;
      count++;
      return root.val == val;
  }
  public int countUnivalSubtrees(TreeNode root) {
      all(root, 0);
      return count;
  }
}
public class Solution {
    int count;

    public int countUnivalSubtrees(TreeNode root) {
        count = 0;
        helper(root);
        return count;
    }

    boolean helper(TreeNode root) {
        if (root == null) return true;

        boolean left = helper(root.left);
        boolean right = helper(root.right);

        if (left && right &&
           (root.left == null || root.val == root.left.val) &&
           (root.right == null || root.val == root.right.val)) {
            count++;
            return true;
        }

        return false;
    }
}
