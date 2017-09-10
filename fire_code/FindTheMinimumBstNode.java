//Find the Minimum BST Node
//Given a Binary Search Tree , return the node with the minimum data.
//Example:  
//       4                                  
//      / \                              
//     2   8     
//        / \                     
//       5  10                  
//Output ==> 2

public class FindTheMinimumBstNode {

  public TreeNode findMin(TreeNode root) {
      TreeNode min = root;
      if( root == null || root.left == null) return min;
      min = findMin(root.left);
      return min;
  }

}
