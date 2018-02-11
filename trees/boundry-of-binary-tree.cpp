//Boundary of Binary Tree
//Given a binary tree, return the values of its boundary in anti-clockwise direction starting from root. Boundary includes left boundary, leaves, and right boundary in order without duplicate nodes.
//Left boundary is defined as the path from root to the left-most node.
//Right boundary is defined as the path from root to the right-most node.
//If the root doesn't have left subtree or right subtree, then the root itself is left boundary or right boundary. Note this definition only applies to the input binary tree, and not applies to any subtrees.
//The left-most node is defined as a leaf node you could reach when you always firstly travel to the left subtree if exists. If not, travel to the right subtree. Repeat until you reach a leaf node.
//The right-most node is also defined by the same way with left and right exchanged.
//Example 1
//Input:
//  1
//   \
//    2
//   / \
//  3   4
//Ouput:
//[1, 3, 4, 2]
//Explanation:
//The root doesn't have left subtree, so the root itself is left boundary.
//The leaves are node 3 and 4.
//The right boundary are node 1,2,4. Note the anti-clockwise direction means you should output reversed right boundary.
//So order them in anti-clockwise without duplicates and we have [1,3,4,2].
//Example 2
//Input:
//    ____1_____
//   /          \
//  2            3
// / \          /
//4   5        6
//   / \      / \
//  7   8    9  10
//Ouput:
//[1,2,4,7,8,9,10,6,3]
//Explanation:
//The left boundary are node 1,2,4. (4 is the left-most node according to definition)
//The leaves are node 4,7,8,9,10.
//The right boundary are node 1,3,6,10. (10 is the right-most node).
//So order them in anti-clockwise without duplicate nodes we have [1,2,4,7,8,9,10,6,3].
//


//######################################### Recursion  #########################################

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public List < Integer > boundaryOfBinaryTree(TreeNode root) {
        List < Integer > left_boundary = new LinkedList < > (), right_boundary = new LinkedList < > (), leaves = new LinkedList < > ();
        preorder(root, left_boundary, right_boundary, leaves, 0);
        left_boundary.addAll(leaves);
        left_boundary.addAll(right_boundary);
        return left_boundary;
    }

    public boolean isLeaf(TreeNode cur) {
        return (cur.left == null && cur.right == null);
    }

    public boolean isRightBoundary(int flag) {
        return (flag == 2);
    }

    public boolean isLeftBoundary(int flag) {
        return (flag == 1);
    }

    public boolean isRoot(int flag) {
        return (flag == 0);
    }

    public int leftChildFlag(TreeNode cur, int flag) {
        if (isLeftBoundary(flag) || isRoot(flag))
            return 1;
        else if (isRightBoundary(flag) && cur.right == null)
            return 2;
        else return 3;
    }

    public int rightChildFlag(TreeNode cur, int flag) {
        if (isRightBoundary(flag) || isRoot(flag))
            return 2;
        else if (isLeftBoundary(flag) && cur.left == null)
            return 1;
        else return 3;
    }

    public void preorder(TreeNode cur, List < Integer > left_boundary, List < Integer > right_boundary, List < Integer > leaves, int flag) {
        if (cur == null)
            return;
        if (isRightBoundary(flag))
            right_boundary.add(0, cur.val);
        else if (isLeftBoundary(flag) || isRoot(flag))
            left_boundary.add(cur.val);
        else if (isLeaf(cur))
            leaves.add(cur.val);
        preorder(cur.left, left_boundary, right_boundary, leaves, leftChildFlag(cur, flag));
        preorder(cur.right, left_boundary, right_boundary, leaves, rightChildFlag(cur, flag));
    }
}


//######################################### Stack  #########################################
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {

    public boolean isLeaf(TreeNode t) {
        return t.left == null && t.right == null;
    }

    public void addLeaves(List<Integer> res, TreeNode root) {
        if (isLeaf(root)) {
            res.add(root.val);
        } else {
            if (root.left != null) {
                addLeaves(res, root.left);
            }
            if (root.right != null) {
                addLeaves(res, root.right);
            }
        }
    }

    public List<Integer> boundaryOfBinaryTree(TreeNode root) {
        ArrayList<Integer> res = new ArrayList<>();
        if (root == null) {
            return res;
        }
        if (!isLeaf(root)) {
            res.add(root.val);
        }
        TreeNode t = root.left;
        while (t != null) {
            if (!isLeaf(t)) {
                res.add(t.val);
            }
            if (t.left != null) {
                t = t.left;
            } else {
                t = t.right;
            }

        }
        addLeaves(res, root);
        Stack<Integer> s = new Stack<>();
        t = root.right;
        while (t != null) {
            if (!isLeaf(t)) {
                s.push(t.val);
            }
            if (t.right != null) {
                t = t.right;
            } else {
                t = t.left;
            }
        }
        while (!s.empty()) {
            res.add(s.pop());
        }
        return res;
    }
}
//######################################### Recursion #########################################
public List<Integer> boundaryOfBinaryTree(TreeNode root) {
    //corner case
    List<Integer> list = new ArrayList<>();
    if (root == null)
        return list;

    list.add(root.val);

    dfs(root.left, true, false, list);//left half tree
    dfs(root.right, false, true, list);//right half tree

    return list;
}

//PreOrder on the left half tree to fetch left Border elements, InOrder on the left and right half tree to fetch leaf elements PostOrder on the right half tree to fetch right Border elements
private void dfs(TreeNode root, boolean isLeftBound, boolean isRightBound, List<Integer> list) {
    //base case
    if (root == null)
        return;
    //take care of leftBorder elements in preOrder
    if (isLeftBound)
        list.add(root.val);

    dfs(root.left, isLeftBound, isRightBound && root.right == null, list); //->left Chk>right

    //take care of leaf nodes in AnyOrder, I just use InOrder
    if (!isLeftBound && !isRightBound && root.left == null && root.right == null)
        list.add(root.val);

    dfs(root.right, isLeftBound && root.left == null, isRightBound, list); //->right Chk>left

    //take care of rightBorder elements in postOrder
    if (isRightBound)
        list.add(root.val);
}

//######################################### Recursion #########################################
//1. node.left is left bound if node is left bound;
//2. node.right could also be left bound if node is left bound && node has no right child;
//3. Same applys for right bound;
//4. if node is left bound, add it before 2 child - pre order;
//5. if node is right bound, add it after 2 child - post order;
//6. A leaf node that is neither left or right bound belongs to the bottom line;
class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> bounds;
        if (root) {
            bounds.push_back(root->val);
            getBounds(root->left, bounds, true, false);
            getBounds(root->right, bounds, false, true);
        }
        return bounds;
    }

private:
    //Lt boundry-> children -> Rt boundry
    void getBounds(TreeNode* node, vector<int>& res, bool lb, bool rb) {
        if (!node)  return;
        if (lb) {
          res.push_back(node->val);
        }
        if (!lb && !rb && !node->left && !node->right) {
          res.push_back(node->val);
        }
        getBounds(node->left, res, lb, rb && !node->right);
        getBounds(node->right, res, lb && !node->left, rb);
        if (rb) {
          res.push_back(node->val);
        }
    }
};

//######################################### O(N) + Recursion #########################################
//nodes in the process. A single flag is used to designate the type of node during the preorder traversal.
//Its values are: 0 - root, 1 - left boundary node, 2 - right boundary node, 3 - middle node.
public List<Integer> boundaryOfBinaryTree(TreeNode root) {
    List<Integer> left = new LinkedList<>(), right = new LinkedList<>();
    preorder(root, left, right, 0);
    left.addAll(right);
    return left;
}

public void preorder(TreeNode cur, List<Integer> left, List<Integer> right, int flag) {
    if (cur == null) return;
    if (flag == 2) right.add(0, cur.val);
    else if (flag <= 1 || cur.left == null && cur.right == null) left.add(cur.val);
    preorder(cur.left, left, right, flag <= 1 ? 1 : (flag == 2 && cur.right == null) ? 2 : 3);
    preorder(cur.right, left, right, flag % 2 == 0 ? 2 : (flag == 1 && cur.left == null) ? 1 : 3);
}

//######################################### python #########################################
//######################################### Recursion #########################################
def boundaryOfBinaryTree(self, root):
    # The main idea is to carry the flag isleft and isight
    # in the dfs steps to help decide when to add node
    # values to the boundary array.
    if not root: return []
    boundary = [root.val]
    def dfs(root, isleft, isright):
        if root:
            # append when going down from the left or at leaf node
            if (not root.left and not root.right) or isleft:
                boundary.append(root.val)

            if root.left and root.right:
                dfs(root.left, isleft, False)
                dfs(root.right, False, isright)
            else:
                dfs(root.left,  isleft, isright)
                dfs(root.right, isleft, isright)

            # append to boundary when coming up from the right
            if (root.left or root.right) and isright:
                boundary.append(root.val)

    dfs(root.left, True, False)
    dfs(root.right, False, True)
    return boundary
//######################################### Recursion #########################################
class Solution(object):
    def boundaryOfBinaryTree(self, root):
        def dfs_leftmost(node):
            if not node or not node.left and not node.right:
                return
            boundary.append(node.val)
            if node.left:
                dfs_leftmost(node.left)
            else:
                dfs_leftmost(node.right)

        def dfs_leaves(node):
            if not node:
                return
            dfs_leaves(node.left)
            if node != root and not node.left and not node.right:
                boundary.append(node.val)
            dfs_leaves(node.right)

        def dfs_rightmost(node):
            if not node or not node.left and not node.right:
                return
            if node.right:
                dfs_rightmost(node.right)
            else:
                dfs_rightmost(node.left)
            boundary.append(node.val)

        if not root:
            return []
        boundary = [root.val]
        dfs_leftmost(root.left)
        dfs_leaves(root)
        dfs_rightmost(root.right)
        return boundary

// vim: set sw=2 sts=2 tw=120 et nospell :
