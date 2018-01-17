import java.util.*;
// Given a binary tree, write a method to perform the inorder traversal
// iteratively.
// Append the data of each node visited to an ArrayList. Return an empty
// Arraylist in the case of an empty tree.
// Example:
//     1
//    / \
//   2   3     ==> 4251637
//  / \ / \
// 4  5 6  7

public class IterativeInorderTraversal {
  ArrayList<Integer> aList = new ArrayList<>();
  public ArrayList<Integer> inorderItr(TreeNode root) {
    if (root == null) {
      return aList;
    }
    TreeNode curr = root;
    TreeNode prev = null;
    Stack<TreeNode> stk = new Stack<>();
    while (curr != null || !stk.isEmpty()) {
      if (curr != null) {
        stk.push(curr);
        curr = curr.left;
      } else {
        curr = stk.pop();
        aList.add(curr.data);
        curr = curr.right;
      }
      // if(!stk.isEmpty()) {
      //     curr = stk.pop();
      //     aList.add(curr.data);
      // }
      // while(prev != curr && curr.right != null) stk.push(curr.right);
      // while(prev != curr && curr.left != null) stk.push(curr.left);
      // stk.push(curr);
      // prev = curr;
    }
    return aList;
  }
}
