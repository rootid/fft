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
//Longest consecutive sequence path is 2-3,not 3-2-1, so return 2.

//######################################### Top-down  ######################################### 
//TC : o(n) , SC: o(n)
private int maxLength = 0;
public int longestConsecutive(TreeNode root) {
    dfs(root, null, 0);
    return maxLength;
}

private void dfs(TreeNode p, TreeNode parent, int length) {
    if (p == null) return;
    length = (parent != null && p.val == parent.val + 1) ? length + 1 : 1;
    maxLength = Math.max(maxLength, length);
    dfs(p.left, p, length);
    dfs(p.right, p, length);
}


//######################################### Top-down/Preorder ######################################### 
//TC : o(n) , SC: o(n)
public int longestConsecutive(TreeNode root) {
    return dfs(root, null, 0);
}

private int dfs(TreeNode p, TreeNode parent, int length) {
    if (p == null) return length;
    length = (parent != null && p.val == parent.val + 1) ? length + 1 : 1;
    return Math.max(length, Math.max(dfs(p.left, p, length),
                                     dfs(p.right, p, length)));
}

//######################################### Bottom-up/ Postorder ######################################### 
//TC : o(n) , SC: o(n)
private int maxLength = 0;
public int longestConsecutive(TreeNode root) {
    dfs(root);
    return maxLength;
}

private int dfs(TreeNode p) {
    if (p == null) return 0;
    int L = dfs(p.left) + 1;
    int R = dfs(p.right) + 1;
    if (p.left != null && p.val + 1 != p.left.val) {
        L = 1; //update L = 1 when conecutive seq not found
    }
    if (p.right != null && p.val + 1 != p.right.val) {
        R = 1;
    }
    int length = Math.max(L, R);
    maxLength = Math.max(maxLength, length);
    return length;
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

