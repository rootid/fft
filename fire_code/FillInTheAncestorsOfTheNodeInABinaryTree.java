import java.util.*;
// Given a binary tree's root node, an empty ArrayList and an integer nodeData,
// write a method that finds a target node - N with data = nodeData and
// populates the ArrayList with the data of the ancestor nodes of N - added from
// the bottom - up.
// Example:
//       1
//      / \          
//     2   3
//    / \ / \        
//   4  5 6  7
// Node: 5 ==> [2, 1]

public class FillInTheAncestorsOfTheNodeInABinaryTree {
  // Populate the list of ancestors from bottom to top in the below list.
  public ArrayList<Integer> ancestorsList = new ArrayList<Integer>();
  public boolean printAncestors(TreeNode root, int nodeData) {
    if (root == null) {
      return false;
    }
    if (root.data == nodeData) {
      return true;
    }
    if (printAncestors(root.left, nodeData) ||
        printAncestors(root.right, nodeData)) {
      ancestorsList.add(root.data);
      return true;
    }
    return false;
  }
}
