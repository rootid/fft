//Distance of a node from the root
//Given the root of a Binary Tree  and an integer that represents the data value of a TreeNode present in the tree, write a method - pathLengthFromRoot that returns the distance between the root and that node. You can assume that the given key exists in the tree. The distance is defined as the minimum number of nodes that must be traversed to reach the target node.
//Example: 
//       1
//      / \
//     2   3
//      \   \     
//       4   5
//pathLengthFromRoot(root,5) => 3
//pathLengthFromRoot(root,1) => 1
//pathLengthFromRoot(root,3) => 2

public class DistanceOfANodeFromTheRoot {
  int ht = 0;
  if (root == null) { // Base case 
      return ht;
  }
  if (root.data == n1 
      || (ht = pathLengthFromRoot(root.left, n1)) > 0 
      || (ht = pathLengthFromRoot(root.right, n1)) > 0) {
      return 1 + ht; //Recurse
  }
  return ht;
}
