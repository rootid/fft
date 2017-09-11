// Find the Diameter of a BST
// Given a BST, write a function to return its diameter. The diameter of a
// Binary Tree is defined as the "Number of nodes on the longest path between
// two leaf nodes".
// Example:
//      20
//    /     \                              
//   15     30
//  /  \      \  diameter ==> 7
// 14  18     35
//    /  \    /
//   17  19  32
public class FindTheDiameterOfABst {
  int maxDia = 0;

  public int diameter(TreeNode root) {
    maxDepth(root);
    return maxDia;
  }

  private int maxDepth(TreeNode root) {
    if (root == null) return 0;
    int left = maxDepth(root.left);
    int right = maxDepth(root.right);
    maxDia = Math.max(maxDia, left + right + 1);
    return Math.max(left, right) + 1;
  }
}
