//Split BST
//Given a Binary Search Tree (BST) with root node root, and a target value V,
//split the tree into two subtrees where one subtree has nodes that are all
//smaller or equal to the target value, while the other subtree has all nodes
//that are greater than the target value.  It's not necessarily the case that
//the tree contains a node with value V.
//Additionally, most of the structure of the original tree should remain.
//Formally, for any child C with parent P in the original tree, if they are
//both in the same subtree after the split, then node C should still have the
//parent P.
//You should output the root TreeNode of both subtrees after splitting, in any
//order.
//Example 1:
//Input: root = [4,2,6,1,3,5,7], V = 2
//Output: [[2,1],[4,3,6,null,null,5,7]]
//Explanation:
//Note that root, output[0], and output[1] are TreeNode objects, not arrays.
//The given tree [4,2,6,1,3,5,7] is represented by the following diagram:
//          4
//        /   \
//      2      6
//     / \    / \
//    1   3  5   7
//while the diagrams for the outputs are:
//          4
//        /   \
//      3      6      and    2
//            / \           /
//           5   7         1
//Note:
//    The size of the BST will not exceed 50.
//    The BST is always valid and each node's value is different.
//

//######################################### Recursion #########################################
//TC : O(N), SC : O(N)
//Approach #1: Recursion
//Intuition and Algorithm
//The root node either belongs to the first half or the second half. Let's say
//it belongs to the first half.  Then, because the given tree is a binary
//search tree (BST), the entire subtree at root.left must be in the first half.
//However, the subtree at root.right may have nodes in either halves, so it
//needs to be split.
//Diagram of tree being split
//In the diagram above, the thick lines represent the main child relationships
//between the nodes, while the thinner colored lines represent the subtrees
//after the split.
//Lets say our secondary answer bns = split(root.right) is the result of such a
//split. Recall that bns[0] and bns[1] will both be BSTs on either side of the
//split. The left half of bns must be in the first half, and it must be to the
//right of root for the first half to remain a BST. The right half of bns is
//the right half in the final answer.
//Diagram of how root tree connects to split of subtree at root.right
//The diagram above explains how we merge the two halves of split(root.right)
//with the main tree, and illustrates the line of code root.right = bns[0] in
//the implementations.

class Solution {
    public TreeNode[] splitBST(TreeNode root, int V) {
        if (root == null)
            return new TreeNode[]{null, null};
        else if (root.val <= V) {
            TreeNode[] bns = splitBST(root.right, V);
            root.right = bns[0];
            bns[0] = root;
            return bns;
        } else {
            TreeNode[] bns = splitBST(root.left, V);
            root.left = bns[1];
            bns[1] = root;
            return bns;
        }
    }
}

//######################################### #########################################
public TreeNode[] splitBST(TreeNode root, int V) {
    TreeNode sP = new TreeNode(0), bP = new TreeNode(0);
    split(root, V, sP, bP);
    return new TreeNode[]{sP.right, bP.left};
}
private void split(TreeNode node, int v, TreeNode sP, TreeNode bP) {
    if (node == null) return;
    if (node.val <= v) {
        sP.right = node;
        TreeNode right = node.right;
        node.right = null;
        split(right, v, node, bP);
    } else {
        bP.left = node;
        TreeNode left = node.left;
        node.left = null;
        split(left, v, sP, node);
    }
}
