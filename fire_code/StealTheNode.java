// Steal the Node
// WAP to delete a node from a given
// binary search tree
//.
// Example:
//   4                     4
//  / \                   / \              
// 2   8   delete 10 =>  2   8
//    / \                   /
//   5  10                 5

// 1. Recursively find the node that has the same value as the key, while
// setting the left/right nodes equal to the returned subtree
// 2. Once the node is found, have to handle the below 4 cases
// I. node doesn't have left or right - return null
// II. node only has left subtree- return the left subtree
// III. node only has right subtree- return the right subtree
// IV. node has both left and right - find the minimum value in the right
// subtree, set that value to the currently found node, then recursively delete
// the minimum value in the right subtree
public class StealTheNode {
  // deletedNode = delete (TraverseNode, ket)
  public TreeNode delete(TreeNode root, int key) {
    if (root == null) return null;
    if (key < root.data) {  // find which node to delete
      root.left = delete(root.left, key);
    } else if (key > root.data) {
      root.right = delete(root.right, key);
    } else {
      if (root.left == null && root.right == null) return null;
      if (root.left == null) return root.right;
      if (root.right == null) return root.left;
      TreeNode minNode = getMin(root.right);
      root.data = minNode.data;  // replace with inorder successor
      root.right = delete(root.right, root.data);  // remove extra right node
    }
    return root;
  }

  private TreeNode getMin(TreeNode node) {
    while (node.left != null) {
      node = node.left;
    }
    return node;
  }
}
