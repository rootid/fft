//Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
//Note: If the given node has no in-order successor in the tree, return null.
//Assumption : No duplicates are allowed in the BST.
//
//FAILED CASE : p in below BST should return 2, while the new solution will return 3.
//    2 (p)
//     /  \
//   1     3
//        /  \
//       2    4


//################################# Time complexity : O(h) #################################
//Recursion
public TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
    if(root == null) return root;
    if(root.val <= p.val) return inorderSuccessor(root.right, p);
    TreeNode nxtNode = inorderSuccessor(root.left, p);
    return nxtNode == null ? root : nxtNode;
}

//################################# Time complexity : O(h) #################################
//Only in a balanced BST O(h) = O(log n)
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* succ = nullptr;
    while (root != nullptr) {
        //inorder successor lies in the left sub-tree
        if (p->val < root->val) {
            succ = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return succ;
}


//############################### Ternary style c++ ###############################################
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* candidate = NULL;
    while (root)
        root = (root->val > p->val) ? (candidate = root)->left : root->right;
    return candidate;
}

//############################### Iterative O(h) ###############################################
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    //Optimization
    if (p->right) {
        p = p->right;
        while (p->left)
            p = p->left;
        return p;
    }
    TreeNode* candidate = NULL;
    while (root != p)
        root = (p->val > root->val) ? root->right : (candidate = root)->left;
    return candidate;
}

//
//######################################## O(h) ########################################
//1.  The easier one: p has right subtree, then its successor is just the leftmost child of its right subtree; (leftMost
//rotuine) line # 77
//2.  The harder one: p has no right subtree, then a traversal is needed to find its successor.
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (p -> right) return leftMost(p -> right);
        TreeNode* suc = NULL;
        while (root) {
            if (p->val < root->val) {
                suc = root; //store the first node of the left subtree
                root = root->left;
            } else if (p->val > root->val) {
                root = root->right;
            }
            else break;
        }
        return suc;
    }
private:
    TreeNode* leftMost(TreeNode* node) {
        while (node-> left) node = node-> left;
        return node;
    }
};


////######################################### Java #########################################
public TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
    TreeNode succ = null;
    while (root != null) {
        if (p.val < root.val) {
            succ = root;
            root = root.left;
        }
        else
            root = root.right;
    }
    return succ;
}
//
//######################################### Recursive #########################################
public TreeNode successor(TreeNode root, TreeNode p) {
  if (root == null)
    return null;
  if (root.val <= p.val) {
    return successor(root.right, p); //Given value larger than root
  } else {
    TreeNode left = successor(root.left, p);
    return (left != null) ? left : root;
  }
}

//######################## Avoid unnecessary recursion call line # 77 : successor(root.right, p); ########################
//public TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
//    while (root != null && root.val <= p.val)
//        root = root.right;
//    if (root == null)
//        return null;
//    TreeNode left = inorderSuccessor(root.left, p);
//    return (left != null && left.val > p.val) ? left : root;
//}
//
//######################## Compact version ########################
//public TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
//    while (root != null && root.val <= p.val)
//        root = root.right;
//    TreeNode left = root == null ? null : inorderSuccessor(root.left, p);
//    return (left != null && left.val > p.val) ? left : root;
//}
//
//
//public TreeNode predecessor(TreeNode root, TreeNode p) {
//  if (root == null)
//    return null;
//
//  if (root.val >= p.val) {
//    return predecessor(root.left, p);
//  } else {
//    TreeNode right = predecessor(root.right, p);
//    return (right != null) ? right : root;
//  }
//}

//######################################### Pytonic #########################################
//def inorderSuccessor(self, root, p):
//    succ = None
//    while root:
//        if p.val < root.val:
//            succ = root
//            root = root.left
//        else:
//            root = root.right
//    return succ

/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
