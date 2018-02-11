//Equal Tree Partition
//Given a binary tree with n nodes, your task is to check if it's possible to partition the tree to two trees which have the equal sum of values after removing exactly one edge on the original tree.
//Example 1:
//Input:
//    5
//   / \
//  10 10
//    /  \
//   2   3
//Output: True
//Explanation:
//    5
//   /
//  10
//
//Sum: 15
//   10
//  /  \
// 2    3
//Sum: 15
//Example 2:
//Input:
//    1
//   / \
//  2  10
//    /  \
//   2   20
//Output: False
//Explanation: You can't split the tree into two trees with equal sum after removing exactly one edge on the tree.
//Note:
//    The range of tree node value is in the range of [-100000, 100000].
//    1 <= n <= 10000


//######################################### DFS #########################################
//TC : O(N)
//SC : O(N)
//Approach #1: Depth-First Search
//Intuition and Algorithm
//After removing some edge from parent to child, (where the child cannot be the original root) the subtree rooted at child must be half the sum of the entire tree.
//Let's record the sum of every subtree. We can do this recursively using depth-first search. After, we should check that half the sum of the entire tree occurs somewhere in our recording (and not from the total of the entire tree.)
//Our careful treatment and analysis above prevented errors in the case of these trees:
//
//  0
// / \
//-1  1
//
// 0
//  \
//   0
class Solution {
    Stack<Integer> seen;
    public boolean checkEqualTree(TreeNode root) {
        seen = new Stack();
        int total = sum(root);
        seen.pop();
        if (total % 2 == 0)
            for (int s: seen)
                if (s == total / 2)
                    return true;
        return false;
    }

    public int sum(TreeNode node) {
        if (node == null) return 0;
        seen.push(sum(node.left) + sum(node.right) + node.val);
        return seen.peek();
    }
}

//######################################### HashSet  #########################################
private Set<Integer> set = new HashSet<>();
public boolean checkEqualTree(TreeNode root) {
    if (root == null) return false;
    int t = root.val + dfs(root.left) + dfs(root.right);
    return (t % 2 == 0) && set.contains(t / 2);
}
private int dfs(TreeNode n) {
    if (n == null) return 0;
    int t = n.val + dfs(n.left) + dfs(n.right);
    set.add(t);
    return t;
}

//######################################### HashTable #########################################
//The idea is to use a hash table to record all the different sums of each subtree in the tree. If the total sum of the tree is sum, we just need to check if the hash table constains sum/2.
//The following code has the correct result at a special case when the tree is [0,-1,1], which many solutions dismiss. I think this test case should be added.

public boolean checkEqualTree(TreeNode root) {
    Map<Integer, Integer> map = new HashMap<Integer, Integer>();
    int sum = getsum(root, map);
    if(sum == 0)return map.getOrDefault(sum, 0) > 1;
    return sum%2 == 0 && map.containsKey(sum/2);
}

public int getsum(TreeNode root, Map<Integer, Integer> map ){
    if(root == null)return 0;
    int cur = root.val + getsum(root.left, map) + getsum(root.right, map);
    map.put(cur, map.getOrDefault(cur,0) + 1);
    return cur;
}

//######################################### HashTable #########################################
bool checkEqualTree(TreeNode* root) {
    unordered_map<int, int> map;
    int sum = getsum(root, map);
    if(sum == 0)return map[sum] > 1;
    return sum%2 == 0 && map.count(sum/2);
}

int getsum(TreeNode* root,  unordered_map<int, int>& map){
    if(root == NULL)return 0;
    int cur = root->val + getsum(root->left, map) + getsum(root->right, map);
    map[cur]++;
    return cur;
}

