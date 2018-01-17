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

//######################################### pytonic ######################################### 
//
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
