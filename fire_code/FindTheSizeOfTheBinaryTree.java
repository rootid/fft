// Find the size of the Binary Tree
// Given a binary tree, write a method to return its size. The size of a tree is
// the number of nodes it contains.
// Examples:
//     1
//    / \             
//   2   3     ==>  7
//  / \ / \           
// 4  5 6  7

public class FindTheSizeOfTheBinaryTree {
  public int size(TreeNode root) {
    if (root == null) {
      return 0;
    }
    int leftNodes = size(root.left);
    int rtNodes = size(root.right);
    return 1 + leftNodes + rtNodes;
  }
}
