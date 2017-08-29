//Binary Tree Longest Consecutive Sequence
//Given a binary tree, find the length of the longest consecutive sequence path.
//The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).
//For example,
//   1
//    \
//     3
//    / \
//   2   4
//        \
//         5
//Longest consecutive sequence path is 3-4-5, so return 3.
//   2
//    \
//     3
//    / 
//   2    
//  / 
// 1
//Longest consecutive sequence path is 2-3,not3-2-1, so return 2.

//######################################### DFS ######################################### 
//Send current value+1 to next level as a target
public class Solution {
    private int max = 0;
    public int longestConsecutive(TreeNode root) {
        if(root == null) return 0;
        helper(root, 0, root.val);
        return max;
    }
    
    public void helper(TreeNode root, int cur, int target){
        if(root == null) return;
        if(root.val == target) cur++;
        else cur = 1;
        max = Math.max(cur, max);
        helper(root.left, cur, root.val + 1);
        helper(root.right, cur, root.val + 1);
    }
}

//######################################### DFS ######################################### 
public class Solution {
    public int longestConsecutive(TreeNode root) {
        return (root==null)?0:Math.max(dfs(root.left, 1, root.val), dfs(root.right, 1, root.val));
    }
    
    public int dfs(TreeNode root, int count, int val){
        if(root==null) return count;
        count = (root.val - val == 1)?count+1:1;
        int left = dfs(root.left, count, root.val);
        int right = dfs(root.right, count, root.val);
        return Math.max(Math.max(left, right), count);
    }
}


//######################################### DFS ######################################### 
public int longestConsecutive(TreeNode root) {
	if (root == null) {
		return 0;
	}
    return DFS(root, root.val + 1, 1, 1);
}

private int DFS(TreeNode node, int target, int curr, int max) {
	if (node == null) {
		return max;
	}
	if (node.val == target) {
		curr++;
		max = Math.max(max, curr);
	} else { 
		curr = 1;
	}
	return Math.max(DFS(node.left, node.val + 1, curr, max), DFS(node.right, node.val + 1, curr, max));
}


//######################################### DFS ######################################### 
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        return search(root, nullptr, 0);
    }
    
    int search(TreeNode *root, TreeNode *parent, int len) {
        if (!root) return len;
        len = (parent && root->val == parent->val + 1)?len+1:1;
        return max(len, max(search(root->left, root, len), search(root->right, root, len)));
    }
};


//######################################### DFS + recursive ######################################### 
class Solution(object):
    def longestConsecutive(self, root):
        
        def _dfs(node, parent, cur_l):
            if not node:
                return cur_l
            if parent == None or node.val != parent + 1:
                cur_l = 0
            cur_l += 1
            return max(_dfs(node.left, node.val, cur_l), _dfs(node.right, node.val, cur_l), cur_l)
            
        return _dfs(root, None, 0)

//######################################### BFS + Iterative ######################################### 
//Every node is attached with a property "length" when pushed into the queue. 
//It is the length of longest consecutive sequence end with that node. The answer is then the max of all popped lengths. 
from collections import deque
def longestConsecutive(self, root):
    if not root:
        return 0
    ans, dq = 0, deque([[root, 1]])
    while dq:
        node, length = dq.popleft()
        ans = max(ans, length)
        for child in [node.left, node.right]:
            if child:
                l = length + 1 if child.val == node.val + 1 else 1
                dq.append([child, l])
    return ans


//######################################### DFS + Iterative ######################################### 
//Every node is attached with a property "length" when pushed into the stack. 
//It is the length of longest consecutive sequence end with that node. The answer is then the max of all popped lengths. 
def longestConsecutive(self, root):
    if not root:
        return 0
    ans, stack = 0, [[root, 1]]
    while stack:
        node, length = stack.pop()
        ans = max(ans, length)
        for child in [node.left, node.right]:
            if child:
                l = length + 1 if child.val == node.val + 1 else 1
                stack.append([child, l])
    return ans

