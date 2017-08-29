//Binary Tree Longest Consecutive Sequence II
//Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.
//Especially, this path can be either increasing or decreasing. For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not valid. On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.
//Example 1:
//Input:
//        1
//       / \
//      2   3
//Output: 2
//Explanation: The longest consecutive path is [1, 2] or [2, 1].
//Example 2:
//Input:
//        2
//       / \
//      1   3
//Output: 3
//Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
//


//######################################### In order traversal ######################################### 
public int longestConsecutive(TreeNode root) {
    return helper(root, null);
}

private int helper(TreeNode root, int pre) {
    if (root == null) {
        return 0;
    }
    int left = helper(root.left, root.val);
    int right = helper(root.right, root.val);
    if (left * right < 0) {
        max = Math.max(max, 1 + Math.abs(left) + Math.abs(right));
    } else {
        max = Math.max(max, 1 + Math.max(Math.abs(left), Math.abs(right)));
    }
    if (root.val - pre == 1) {  //increasing seq
        return 1 + Math.max(0, Math.max(left, right));
    }
    if (root.val - pre == -1) { //-ve : decreasing seq
        return -1 + Math.min(0, Math.min(left, right));
    }
    return 0;
}

//######################################### Post order traversal ######################################### 
public class Solution {
    int max = 0;
    class Result {
        TreeNode node;
        int inc;
        int des;
    }
    public int longestConsecutive(TreeNode root) {
        traverse(root);
        return max;
    }
    
    private Result traverse(TreeNode node) {
        if (node == null) return null;
        Result left = traverse(node.left);
        Result right = traverse(node.right);
        Result curr = new Result();
        curr.node = node;
        curr.inc = 1;
        curr.des = 1;
        
        if (left != null) {
            if (node.val - left.node.val == 1) {
                curr.inc = Math.max(curr.inc, left.inc + 1);
            } else if (node.val - left.node.val == -1) {
                curr.des = Math.max(curr.des, left.des + 1);
            }
        }
        
        if (right != null) {
            if (node.val - right.node.val == 1) {
                curr.inc = Math.max(curr.inc, right.inc + 1);
            }
            else if (node.val - right.node.val == -1) {
                curr.des = Math.max(curr.des, right.des + 1);
            }
        }
        max = Math.max(max, curr.inc + curr.des - 1);
        return curr;
    }
}

//######################################### Python : DFS ######################################### 
class Solution(object):
    def longestConsecutive(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def dfs(node, parent):
            if not node:
                return 0, 0
            li, ld = dfs(node.left, node)
            ri, rd = dfs(node.right, node)
            l[0] = max(l[0], li + rd + 1, ld + ri + 1)
            if node.val == parent.val + 1:
                return max(li, ri) + 1, 0
            if node.val == parent.val - 1:
                return 0, max(ld, rd) + 1
            return 0, 0
        l = [0]
        dfs(root, root)
        return l[0]

//######################################### LCS : DFS ######################################### 
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        int longest = 0;
        dfs(root, root, longest);
        return longest;
    }

    pair<int, int> dfs(TreeNode* node, TreeNode* parent, int& longest) {
        if ( NULL == node ) {
            return make_pair(0, 0); //store increasing and and decreasing count
        }
        auto left = dfs(node->left, node, longest);
        auto right = dfs(node->right, node, longest);
        longest = max(longest, left.first + right.second + 1);
        longest = max(longest, left.second + right.first + 1);
        int inc = 0, dec = 0;
        if ( node->val == parent->val + 1 ) {
            inc = max(left.first, right.first) + 1;
        }
        if ( node->val == parent->val - 1 ) {
            dec = max(left.second, right.second) + 1;
        }
        return make_pair(inc, dec);
    }
};

//######################################### Flow analysis ######################################### 
//I used sort of flow idea, you can treat the node with lower value as a source and the node with higher value as a sink.
//Just pick one flow direction you like.
//I used ret[] to store the "in-flow" and "out-flow" from the current node to its left/ right child.
//That is {left in-flow, left out-flow, right in-flow, right out-flow}.
//For example, if there is only one single node, ret[] = {1,1,1,1}.
//If the tree is
//
//     2
//   /   \
// 1       3
//Both node 1 and 3 return ret[] = {1,1,1,1}.
//Since node 2's value is bigger than 1, node 2's ret[1] = 1 + node 1's max "in-flow".
//The in-flow and out-flow going through the current node in different directions (left child -> current node -> right child or the other direction)
//is the path going through the current node. Compare this path's length with the current max length to get the result.
//As I said in the comment, you can just use a length-2-array to store the flows using positive and negative value to mark
//if it is an in-flow or out-flow. The reason I used length-4-array because it is easier to tell.

int maxlen;
public int longestConsecutive(TreeNode root) {
    maxlen = 0;
    if(root==null) return maxlen;
    incdecPath(root);
    return maxlen;
}
private int[] incdecPath(TreeNode curr){
    int[] ret = {1,1,1,1}; // index 0 and 1 used to record from current node to left node. index 0 used to record the length pointing from current node to current.left.  
   //Of course, you can use a 2D array here using positive and negative numbers to mark the "flow" direction.
    if(curr.left!=null){
        int[] leftchild = incdecPath(curr.left);
        if(curr.val - curr.left.val == 1){
            ret[0] += Math.max(leftchild[0], leftchild[2]);
        }
        if(curr.val - curr.left.val == -1){
            ret[1] += Math.max(leftchild[1], leftchild[3]);
        }
    }
    if(curr.right!=null){
        int[] rightchild = incdecPath(curr.right);
        if(curr.val - curr.right.val == 1){
            ret[2] += Math.max(rightchild[0], rightchild[2]);
        }
        if(curr.val - curr.right.val == -1){
            ret[3] += Math.max(rightchild[1], rightchild[3]);
        }
    }
    maxlen = Math.max(maxlen,Math.max(ret[0] + ret[3], ret[1] + ret[2]) - 1);
    return ret;
}
