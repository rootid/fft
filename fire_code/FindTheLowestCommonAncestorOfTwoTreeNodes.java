// Find the Lowest Common Ancestor of Two Tree Nodes
// Given a binary tree and two tree nodes, write a method to find
// LCA
//(Lowest Common Ancestor) of the two nodes.
// Example:
//       1
//      / \            
//     2   3
//    / \ / \       
//   4  5 6  7
//    ==>
// LCA
// of 6 and 4 is 1,
//
// LCA
// of 4 and 5 is 2.

public class FindTheLowestCommonAncestorOfTwoTreeNodes {
  public TreeNode findLCA(TreeNode root, TreeNode a, TreeNode b) {
    if (root == null || root == a || root == b) {
      return root;
    }
    TreeNode rL = findLCA(root.left, a, b);
    TreeNode rR = findLCA(root.right, a, b);
    if (rL != null && rR != null) return root;
    if (rL == null) return rR;
    return rL;
  }
}
