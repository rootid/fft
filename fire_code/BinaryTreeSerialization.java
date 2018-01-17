import java.util.*;
// Binary Tree Serialization
// In Computer Science, serialization is the process of converting objects or
// data structures into a sequence (or series) of characters that can be stored
// easily in a file / database table or transmitted across a network. Serialized
// objects need to be de-serialized to create a semantically identical clone of
// the original object, before being used in programs. You're given the root
// node of a binary tree - TreeNode root in the method serializeTree. This
// method should serialize the binary tree and output a String str, which is
// then used as an input parameter for the method restoreTree. restoreTree
// should create a Binary Tree that is structurally identical to the one you
// serialized and return the root node of the tree. Your task is to fill in the
// logic for these 2 methods. Don't worry about passing the serialized String to
// restoreTree - that will be done automatically when you run your code. Feel
// free to use any notation you prefer when serializing the binary tree. The
// choice of traversal algorithm is also open - but try and limit the time
// complexity of both methods to O(n).
// Note:
// Your serialized String will be used to restore the tree. Be sure to use the
// same format and notation in restoreTree that you use to serialize in
// serializeTree .
// Example:
//     1
//    / \
//   2   3
// Serialization :
// Output => "1,2,3"
// Restoring Tree from "1,2,3" :
// Output ->
//     1
//    / \
//   2   3
public class BinaryTreeSerialization {
  //##################### BFS #####################
  public String serializeTree(TreeNode root) {
    String result = "";
    Queue<TreeNode> q = new LinkedList<>();
    if (root != null) {
      q.offer(root);
      StringBuffer sb = new StringBuffer();
      while (!q.isEmpty()) {
        TreeNode tmp = q.poll();
        if (tmp == null)
          sb.append("null,");
        else {
          sb.append(String.valueOf(tmp.data));
          sb.append(",");
          q.offer(tmp.left);
          q.offer(tmp.right);
        }
      }
      return sb.toString();
    }
    return result;
  }

  //### Restore with BFS traversal ###
  public TreeNode restoreTree(String str) {
    TreeNode root = null;
    TreeNode tmp = null;
    String[] strArr = str.split(",");
    if (strArr.length <= 1) {
      return root;
    }
    root = new TreeNode(Integer.parseInt(strArr[0]));
    TreeNode curr = root;
    Queue<TreeNode> q = new LinkedList<>();
    boolean isLeft = true;

    for (int i = 1; i < strArr.length - 1; i++) {
      // Alternatively :
      if (!strArr[i].equals("null")) {
        tmp = new TreeNode(Integer.parseInt(strArr[i]));
        if (isLeft)
          curr.left = tmp;
        else
          curr.right = tmp;
        q.offer(tmp);
      }
      isLeft = !isLeft;
      if (isLeft && !q.isEmpty()) {  // Visit next level that starts from left
        curr = q.poll();
      }
    }
    return root;
  }
}
