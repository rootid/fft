//Minimum Distance Between BST Nodes
//Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the values of any two different nodes in the tree.
//Example :
//Input: root = [4,2,6,1,3,null,null]
//Output: 1
//Explanation:
//Note that root is a TreeNode object, not an array.
//The given tree [4,2,6,1,3,null,null] is represented by the following diagram:
//          4
//        /   \
//      2      6
//     / \
//    1   3
//while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and node 2.
//Note:
//    The size of the BST will be between 2 and 100.
//    The BST is always valid, each node's value is an integer, and each node's value is different.

//######################################### Inorder Tvsal #########################################

class Solution {

    Integer minDiff = Integer.MAX_VALUE, pre = null;

    public int minDiffInBST(TreeNode root) {
        if (root.left != null) minDiffInBST(root.left);
        if (pre != null) minDiff = Math.min(minDiff, root.val - pre);
        pre = root.val;
        if (root.right != null) minDiffInBST(root.right);
        return minDiff;
    }
}

//######################################### Write to Array #########################################
//Write all the values to an array, then sort it. The minimum distance must occur between two adjacent values in the sorted list.
//Time Complexity: O(NlogN), where N  is the number of nodes in the tree. The complexity comes from the sorting operation.
//Space Complexity: O(N), the size of vals.
class Solution {
    List<Integer> vals;
    public int minDiffInBST(TreeNode root) {
        vals = new ArrayList();
        dfs(root);
        Collections.sort(vals);

        int ans = Integer.MAX_VALUE;
        for (int i = 0; i < vals.size() - 1; ++i)
            ans = Math.min(ans, vals.get(i+1) - vals.get(i));

        return ans;
    }

    public void dfs(TreeNode node) {
        if (node == null) return;
        vals.add(node.val);
        dfs(node.left);
        dfs(node.right);
    }
}




//######################################### Inorder tvsal #########################################
//Time Complexity: O(N), where NNN is the number of nodes in the tree. We iterate over every node once.
//Space Complexity: O(H), where HHH is the height of the tree. This is the space used by the implicit call stack when calling dfs.
//In a binary search tree, an in-order traversal outputs the values of the tree in order. By remembering the previous value in this order,
//We could iterate over each possible difference, keeping the smallest one.

class Solution {
    Integer prev, ans;
    public int minDiffInBST(TreeNode root) {
        prev = null;
        ans = Integer.MAX_VALUE;
        dfs(root);
        return ans;
    }

    public void dfs(TreeNode node) {
        if (node == null) return;
        dfs(node.left);
        if (prev != null)
            ans = Math.min(ans, node.val - prev);
        prev = node.val;
        dfs(node.right);
    }
}
