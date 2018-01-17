import java.util.*;
// Given a binary tree, write a method to print the tree level by level.
// Example:
//     1
//    / \             
//   2   3
//  / \ / \           
// 4  5 6  7
//  ==>  [1][2, 3][4, 5, 6, 7]
// Note: Each item in the list is an ArrayList of the format [A[], B,[] .....],
// where A[],B[].... are the nodes at a particular level, stored in an
// ArrayList.

public class PrintABinaryTreeLevelByLevel {
  public ArrayList<ArrayList<Integer>> printLevelByLevel(TreeNode root) {
    // ArrayList<ArrayList<Integer>> resultList = new
    // ArrayList<ArrayList<Integer>>();
    ArrayList<ArrayList<Integer>> resultList = new ArrayList<>();
    if (root == null) return resultList;
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    ArrayList<Integer> levelList = new ArrayList<>();
    int alreadyVisited = 1;
    int visitedCnt = 0;
    while (!q.isEmpty()) {
      TreeNode current = q.poll();
      levelList.add(current.data);
      alreadyVisited--;
      if (current.left != null) {
        q.offer(current.left);
        visitedCnt++;
      }
      if (current.right != null) {
        q.offer(current.right);
        visitedCnt++;
      }
      if (alreadyVisited == 0) {
        resultList.add(levelList);
        levelList = null;
        levelList = new ArrayList<>();
        alreadyVisited = visitedCnt;
        visitedCnt = 0;
      }
    }
    return resultList;
  }
}
