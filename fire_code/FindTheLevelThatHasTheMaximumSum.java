import java.util.*;
// Given a binary tree, write a method to return the level that has the maximum
// sum. In case the tree is empty, return -1
// Example:
//       1
//      / \
//     2   3
//    / \ / \  
//   4  5 6  7
//  /
// 8
// Output ==> 2
// Note: Assume that root is at level 0.

public class FindTheLevelThatHasTheMaximumSum {
  //##### Iterative version ####
  public int findMaxSumLevel(TreeNode root) {
    if (root == null) return -1;
    int resultVal = 0;
    int resultLevel = 0;
    int tCnt = 0;
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    int lRVal = 0;
    int lRLvel = -1;
    while (!q.isEmpty()) {
      tCnt = q.size();
      while (tCnt-- > 0) {
        TreeNode tmp = q.poll();
        lRVal += tmp.data;
        if (tmp.left != null) q.offer(tmp.left);
        if (tmp.right != null) q.offer(tmp.right);
      }
      lRLvel++;
      if (lRVal > resultVal) {
        resultVal = lRVal;
        resultLevel = lRLvel;
      }
      lRVal = 0;
    }
    return resultLevel;
  }

  //##### Recursive version ####
  public int findMaxSumLevelRec(TreeNode root) {
    ArrayList<Integer> levelSums = new ArrayList<Integer>();
    dfsSum(root, 0, levelSums);
    if (levelSums.size() == 0) return -1;
    int maxLevel = 0;
    // iterate over all the levels
    for (int level = 0; level < levelSums.size(); level++)
      maxLevel =
          levelSums.get(level) > levelSums.get(maxLevel) ? level : maxLevel;
    return maxLevel;
  }

  private static void dfsSum(TreeNode root, int level,
                             ArrayList<Integer> levelSums) {
    if (root == null) return;
    if (level == levelSums.size()) levelSums.add(0);
    levelSums.set(level, levelSums.get(level) + root.data);
    dfsSum(root.left, level + 1, levelSums);
    dfsSum(root.right, level + 1, levelSums);
  }
}
