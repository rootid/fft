// Given a binary tree, write a method to find and return its deepest node.
// Return null for an empty tree.
// Example:
//       1
//      / \
//     2   3     ==> deepest = 9
//    / \ / \
//   4  5 6  7
//  / \
// 8   9

// DFS approach
public class TheDeepestNode {
  TreeNode deepestNode;
  int deepestLevel = -1;

  public TreeNode findDeepest(TreeNode root) {
    dfs(root, 0);
    return deepestNode;
  }

  private void dfs(TreeNode root, int level) {
    if (root == null) return;
    if (level > deepestLevel) {
      deepestLevel = level;
      deepestNode = root;
    }
    dfs(root.right, level + 1);
    dfs(root.left, level + 1);
  }
}

// void find(Node *root, int level, int &maxLevel, int &res) {
//    if (root != NULL) {
//        find(root->left, ++level, maxLevel, res);
//        // Update level and resue
//        if (level > maxLevel) {
//            res = root->data;
//            maxLevel = level;
//        }
//        find(root->right, level, maxLevel, res);
//    }
//}
//// Returns value of deepest node
// int deepestNode(Node *root) {
//    // Initialze result and max level
//    int res = -1;
//    int maxLevel = -1;
//
//    // Updates value "res" and "maxLevel"
//    // Note that res and maxLen are passed
//    // by reference.
//    find(root, 0, maxLevel, res);
//    return res;
//}
