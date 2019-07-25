//Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right
//to left for the next level and alternate between).
//For example:
//Given binary tree [3,9,20,null,null,15,7],
//    3
//   / \
//  9  20
//    /  \
//   15   7
//return its zigzag level order traversal as:
//[
//  [3],
//  [20,9],
//  [15,7]
//]

//################################ Recursion ################################
public class Solution {
  public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
      List<List<Integer>> sol = new ArrayList<>();
      travel(root, sol, 0);
      return sol;
  }

  private void travel(TreeNode curr, List<List<Integer>> sol, int level) {
      if(curr == null) return;

      if(sol.size() <= level) {
          List<Integer> newLevel = new LinkedList<>();
          sol.add(newLevel);
      }

      List<Integer> collection  = sol.get(level);
      if(level % 2 == 0) collection.add(curr.val);
      else collection.add(0, curr.val);

      travel(curr.left, sol, level + 1);
      travel(curr.right, sol, level + 1);
  }
}
//O(n) solution by using LinkedList along with ArrayList. So insertion in the inner list and outer list are both O(1),
//Using DFS and creating new lists when needed.
//Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right
//to left for the next level and alternate between).
//For example:
//Given binary tree [3,9,20,null,null,15,7],
//    3
//   / \
//  9  20
//    /  \
//   15   7
//return its zigzag level order traversal as:
//[
//  [3],
//  [20,9],
//  [15,7]
//]

//################################ Iteration + No reverse ################################
public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
  List<List<Integer>> res = new ArrayList<>();
  if (root == null) return res;
  Queue<TreeNode> queue = new LinkedList<>();
  queue.add(root);
  boolean zigzag = false;
  while (!queue.isEmpty()) {
      List<Integer> level = new ArrayList<>();
      int cnt = queue.size();
      for (int i = 0; i < cnt; i++) {
          TreeNode node = queue.poll();
          if (zigzag)
              level.add(0, node.val); //prepend the node
          else
              level.add(node.val); //append the tnode
          if (node.left != null)
              queue.add(node.left);
          if (node.right != null)
              queue.add(node.right);
      }
      res.add(level);
      zigzag = !zigzag;
  }
  return res;
}

//################################ Iterative + Deque  ################################
public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
    List<List<Integer>> result = new LinkedList<>();
    if(root == null) return result;
    Queue<TreeNode> visitQ = new ArrayDeque<>();
    visitQ.offer(root);
    boolean isRev = false;
    while(!visitQ.isEmpty()) {
        List<Integer> vList = new ArrayList<>();
        int toBeVisited = visitQ.size();
        for(int i=0;i<toBeVisited;i++) {
            TreeNode tmp = visitQ.poll();
            vList.add(tmp.val);
            if(tmp.left != null) visitQ.offer(tmp.left);
            if(tmp.right != null) visitQ.offer(tmp.right);
        }
      if(isRev == true)
          Collections.reverse(vList);
       result.add(vList);
       isRev = !isRev;
    }
    return result;
}

//################################ Iterative  ################################
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
       vector<vector <int> > result;
       if(!root) {
           return result;
       }
       queue<TreeNode* > q;
       q.push(root);
       vector<int> tmp;
       int visited = 1;
       int level = 0;
       int nxt_visited = 0;
       while(!q.empty()) {
           TreeNode *next = q.front();
           q.pop();
           visited--;
           if(next->left != NULL) {
               q.push(next->left);
               nxt_visited += 1;
           }
           if(next->right != NULL) {
               q.push(next->right);
               nxt_visited += 1;
           }
           tmp.push_back(next->val);
           if(visited == 0) {
               visited =  nxt_visited;
               nxt_visited = 0;
               if(level % 2 != 0) {
                   reverse(tmp.begin(),tmp.end());
               }
               level++;
               result.push_back(tmp);
               tmp.clear();
           }
       }
       return result;
}

int main() {
//[3,9,20,null,null,15,7]
//
  TreeNode *root= new TreeNode (3);
  root->left= new TreeNode (9);
  root->right= new TreeNode (20);
  root->right->left =  new TreeNode (15);
  root->right->right = new TreeNode (7);
  zigzagLevelOrder(root);
}
// vim: set sw=2 sts=2 tw=120 et nospell :
