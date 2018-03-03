//Longest Univalue Path
//Given a binary tree, find the length of the longest path where each node in
//the path has the same value. This path may or may not pass through the root.
//Note: The length of path between two nodes is represented by the number of
//edges between them.
//Example 1:
//Input:
//              5
//             / \
//            4   5
//           / \   \
//          1   1   5
//Output:
//2
//Example 2:
//Input:
//              1
//             / \
//            4   5
//           / \   \
//          4   4   5
//Output:
//2
//Note: The given binary tree has not more than 10000 nodes. The height of the
//tree is not more than 1000.

//#########################################
int longestUnivaluePath(TreeNode* c, TreeNode* r = nullptr) {
    if (c == nullptr) return 0;
    if (r == nullptr) return max(longestUnivaluePath(c, c),
        max(longestUnivaluePath(c->left, nullptr), longestUnivaluePath(c->right, nullptr)));
    return c->val != r->val ? 0 : (c == r ? longestUnivaluePath(c->left, r) + longestUnivaluePath(c->right, r) :
            1 + max(longestUnivaluePath(c->left, r), longestUnivaluePath(c->right, r)));
}

//######################################### Longest univalue #########################################
//The approach is similar to the Diameter of Binary Tree question except
//that we reset the left/right to 0 whenever the current node does not match
//the children node value.
//In the Diameter of Binary Tree question, the path can either go through the
//root or it doesn't.
//Hence at the end of each recursive loop, return the longest length using that
//node as the root so that the node's parent can potentially use it in its
//longest path computation.
//We also use an external variable longest that keeps track of the longest path
//seen so far.
class Solution(object):
    def longestUnivaluePath(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        # Time: O(n)
        # Space: O(n)
        longest = [0]
        def traverse(node):
            if not node:
                return 0
            left_len, right_len = traverse(node.left), traverse(node.right)
            left = (left_len + 1) if node.left and node.left.val == node.val else 0
            right = (right_len + 1) if node.right and node.right.val == node.val else 0
            longest[0] = max(longest[0], left + right)
            return max(left, right)
        traverse(root)
        return longest[0]

//In Python 2 you cannot modify variable references outside of the function.
//In Python 3 there's nonlocal but that does not exist in Python 2.
//Hence this is a common hack where we use an array containing a single value
//and modify that value instead (the reference to the array is preserved).

//######################################### DFS #########################################
class Solution {
    public int longestUnivaluePath(TreeNode root) {
        int[] res = new int[1];
        if (root != null) dfs(root, res);
        return res[0];
    }

    private int dfs(TreeNode node, int[] res) {
        int l = node.left != null ? dfs(node.left, res) : 0;
        int r = node.right != null ? dfs(node.right, res) : 0;
        int resl = node.left != null && node.left.val == node.val ? l + 1 : 0;
        int resr = node.right != null && node.right.val == node.val ? r + 1 : 0;
        res[0] = Math.max(res[0], resl + resr);
        return Math.max(resl, resr);
    }
}


//######################################### DFS #########################################
class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        int lup = 0;
        if (root) dfs(root, lup);
        return lup;
    }

private:
    int dfs(TreeNode* node, int& lup) {
        int l = node->left ? dfs(node->left, lup) : 0;
        int r = node->right ? dfs(node->right, lup) : 0;
        int resl = node->left && node->left->val == node->val ? l + 1 : 0;
        int resr = node->right && node->right->val == node->val ? r + 1 : 0;
        lup = max(lup, resl + resr);
        return max(resl, resr);
    }
};

//VARS
//l is the length of single direction Longest-Univalue-Path start from
//left-child,
//r is the length of single direction Longest-Univalue-Path start from
//right-child,
//resl is the length of single direction Longest-Univalue-Path start from
//parent go left,
//resr is the length of single direction Longest-Univalue-Path start from
//parent go right.
//int dfs(node) returns the Longest-Univalue-Path-Start-At that node, and
//update the result of Longest-Univalue-Path-Across that node through side
//effect.
//It is really hard to name those variables to reflect these concept.
//
//Example:
//
//                ...
//               /
//              4 (res = resl + resr = 3)
//  (resl = 2) / \ (resr= 1)
//    (l = 1) 4   4 (r = 0)
//           /
//          4
//resl is Longest-Univalue-Path-Start-At left node + 1,
//resr is Longest-Univalue-Path-Start-At right node + 1,
//in here the local result of Longest-Univalue-Path-Across at this node is the
//sum of the 2;



//######################################### DFS  #########################################
//Here is my recursive Java solution. A univalue path can be divided into two
//parts:
//The node connecting the left branch and right branch of the univalue path, on
//which a recursion should start. For example in the case below the top 4* is
//the connecting node.
//
//       1
//      / \
//     4*   5
//    / \    \
//   4   4    5
//The left and right branches, along which we should count the edges until
//value changes or null is reached. Actually, it is not guaranteed that both
//left and right branches must exist in the longest univalue path solution, and
//the branch can have zigzags like the following case.
//
//       1
//      / \
//     4   5*
//    / \   \
//   4   4   5
//          / \
//         5   6
//          \
//           5
//To implement the solution in Java, we can create two recursive functions:
//pathLengthCounter(): Do DFS starting from a certain node and keep counting
//the number of nodes with same values until a different value or null is
//reached.
//pathLengthStarter(): Start recursion on a connecting node, and call
//pathLengthCounter() to count the length of its left and right branches if
//exist. Then sum them up to get the total length of the univalue path
//connected by this node. Each time a total length is obtained, compare it with
//the current maximum length stored in a class variable, and update the maximum
//value if the new length is longer. Moreover, the left and right children of
//this node, if exist, can also be connecting nodes for other univalue paths,
//so we recursively call pathLengthStarter() on them.
//After all recursions are done, the longest univalue length is acquired. Sorry
//that I am quite a new coder (it is my first time in contest) and I'd like to
//make the variable name as detailed as possible. Here is the just my way to
//look into this problem and I'm sure there are more concise ways in coding.

class Solution {
    int maxLength;
    public int longestUnivaluePath(TreeNode root) {
        if (root == null) return 0;
        maxLength = 0;
        pathLengthStarter(root);
        return maxLength;
    }

    private void pathLengthStarter(TreeNode root) {
        int thisLength = 0;
        if (root.left != null) {
            thisLength += pathLengthCounter(root.left, root.val, 0);
            pathLengthStarter(root.left);
        }
        if (root.right != null) {
            thisLength += pathLengthCounter(root.right, root.val, 0);
            pathLengthStarter(root.right);
        }
        if (thisLength > maxLength)
            maxLength = thisLength;
    }

    private int pathLengthCounter(TreeNode root, int currVal, int prevLength) {
        if (root == null || root.val != currVal)
            return prevLength;
        else {
            return Math.max(pathLengthCounter(root.left, currVal, prevLength + 1),
                            pathLengthCounter(root.right, currVal, prevLength + 1));
        }
    }
}

