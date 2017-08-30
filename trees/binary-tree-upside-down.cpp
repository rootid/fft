//Binary Tree Upside Down
//Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.
//For example:
//Given a binary tree {1,2,3,4,5},
//    1
//   / \
//  2   3
// / \
//4   5
//return the root of the binary tree [4,5,2,#,#,3,1].
//   4
//  / \
// 5   2
//    / \
//   3   1  

//Transformation
//    1
//   / \
//  2   3
// / \
//4---> 5


//######################################### Recursive ######################################### 
//Space : O(n)
public TreeNode upsideDownBinaryTree(TreeNode root) {
    if(root == null || root.left == null) {
        return root;
    }
    TreeNode newRoot = upsideDownBinaryTree(root.left);
	//Old node update
    root.left.left = root.right;   // node 2 left children
    root.left.right = root;         // node 2 right children
    root.left = null;
    root.right = null;
    return newRoot;
}


//######################################### Iterative  ######################################### 
public TreeNode upsideDownBinaryTree(TreeNode root) {
    TreeNode curr = root;
    TreeNode next = null;
    TreeNode temp = null;
    TreeNode prev = null;
    
    while(curr != null) {
        next = curr.left;
        // swapping nodes now, need temp to keep the previous right child
        curr.left = temp;
        temp = curr.right;
        curr.right = prev;
        
        prev = curr;
        curr = next;
    }
    return prev;
} 


//######################################### Recursive ######################################### 
TreeNode* upsideDownBinaryTree(TreeNode* root) {
    if (!root || !root->left) return root;
    TreeNode* curLeft = root->left;
    TreeNode* curRight = root->right;
    TreeNode* new_root = upsideDownBinaryTree(root->left);
    curLeft->right = root;
    curLeft->left = cur_right;
    root->left = nullptr;
    root->right = nullptr;
    return new_root;
}


//######################################### Recursive ######################################### 
//1.root's right node becomes the left node of the left node of root
//2.root becomes the right node of root's left node
//3.above rules apply on the left edge and return left node along the path.
class Solution(object):
    def upsideDownBinaryTree(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """
        if not root or (not root.left and not root.right):
            return root
        left = self.upsideDownBinaryTree(root.left)
        root.left.left = root.right
        root.left.right = root
        root.left = None
        root.right = None
        return left

//######################################### Iterative stack  ######################################### 
public TreeNode upsideDownBinaryTree(TreeNode root){
        Stack<TreeNode> stack = new Stack<TreeNode>();
        TreeNode head = new TreeNode(0);
        TreeNode cur = head;
        while(root!=null){
            stack.push(root);
            root = root.left;
        }
        while(!stack.isEmpty()){
            TreeNode node = stack.pop();
            cur.right = node;
            if(!stack.isEmpty())
                node.left = stack.peek().right;
            cur = cur.right;
        }
        return head.right;
    }
