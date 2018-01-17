// Given the root of a Binary Tree  and 2 integers that represent the data
// values of any two TreeNodes present in the tree, write a method -
// getNodeDistance that returns the distance between the nodes. You can assume
// that the given keys exist in the tree. The distance between two nodes is
// defined as the minimum number of edges that must be traversed to travel
// between the two nodes.
// Example:
//       1
//      / \
//     2   3
//      \   \     
//       4   5
// getNodeDistance(2,5) => 3

// By now you should know how to find the LCA or Lowest Common Ancestor of two
// nodes in a binary tree, as well as the path length between a given node and
// the root. We are going to simplify this problem by solving smaller
// subproblems and combining the result using the following formula :
// Note:
// pathLen(Root,B) = Distance between the root and node B
// lca(A,B) = Lowest Common Ancestor of nodes A and B
// Formula :
// getNodeDistance(A,B) = pathLen(Root, A) + pathLen(Root, B) - (2 *
// pathLen(Root, lca(A,B))e

// distance from LCA to node1 and node2, which means distance = LCA->node1 +
// LCA->node2?

public class DistanceBetweenTwoNodesInABinaryTree {
  // LCA to node1 and node2, which means distance = LCA->node1 + LCA->node2
  public int getNodeDistance(TreeNode root, int n1, int n2) {
    TreeNode tmp = lca(root, n1, n2);
    int l1 = pathLen(tmp, n1);
    int l2 = pathLen(tmp, n2);
    return l1 + l2;
  }

  private TreeNode lca(TreeNode root, int p, int q) {
    if (root == null || root.data == p || root.data == q) return root;
    TreeNode left = lca(root.left, p, q);
    TreeNode right = lca(root.right, p, q);
    if (left == null) return right;
    if (right == null) return left;
    return root;
  }

  private int pathLen(TreeNode root, int n) {
    if (root == null) return -1;
    int dist = -1;
    if (root.data == n || (dist = pathLen(root.left, n)) >= 0 ||
        (dist = pathLen(root.right, n)) >= 0)
      return dist + 1;

    return dist;
  }

  // public int getNodeDistance(TreeNode root, int n1, int n2) {
  //    return nodeDistance(root, n1, n2, 0)[1];
  //}
  //
  // private int[] nodeDistance(TreeNode root, int n1, int n2, int level) {
  //    if (root == null) return new int[] {0, -1};
  //    else {
  //        int[] left = nodeDistance(root.left, n1, n2, level + 1);
  //        int[] right = nodeDistance(root.right, n1, n2, level + 1);
  //        //one of the nodes is root node
  //        if (root.data == n1 || root.data == n2) {
  //            if (left[1] > -1) return new int[] {1, 1 + left[1]};
  //            if (right[1] > -1) return new int[] {1, 1 + right[1]};
  //            return new int[] {0, 0};
  //
  //        } else if (left[1] > -1 && right[1] > -1) {
  //            return new int[] {1, 2 + left[1] + right[1]};
  //
  //        } else if (left[1] > -1) {
  //            if (left[0] == 0) return new int[] {0, 1 + left[1]};
  //            else return new int[] {1, left[1]};
  //        } else {
  //            if (right[0] == 0) return new int[] {0, (right[1] > -1) ? (1 +
  //            right[1]) : -1};
  //            else return new int[] {1, right[1]};
  //        }
  //    }
  //}
}
