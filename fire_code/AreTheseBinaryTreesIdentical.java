// Are these Binary Trees Identical | AreTheseBinaryTreesIdentical.java
// Given two binary trees, determine if they are identical. If they are, return
// true otherwise return false.
// Example:
//       1              1
//      / \            / \
//     2   3    !=    2   3
//    / \ / \        / \ / \
//   4  5 6  7      4  5 6  7
//  /
// 8

public class AreTheseBinaryTreesIdentical {
  public boolean isIdentical(TreeNode root1, TreeNode root2) {
    if (root1 == null && root2 == null) return true;
    if (root1 == null || root2 == null) return false;
    if (root1.data != root2.data) return false;
    return isIdentical(root1.left, root2.left) &&
        isIdentical(root1.right, root2.right);
  }
}
