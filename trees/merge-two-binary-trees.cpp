//Merge Two Binary Trees
//Given two binary trees and imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not.
//You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of new tree.
//Example 1:
//Input: 
//	Tree 1                     Tree 2                  
//          1                         2                             
//         / \                       / \                            
//        3   2                     1   3                        
//       /                           \   \                      
//      5                             4   7                  
//Output: 
//Merged tree:
//	     3
//	    / \
//	   4   5
//	  / \   \ 
//	 5   4   7
//Note: The merging process must start from the root nodes of both trees.

//#################################### Preorder traersal with new Tree  #################################### 
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    if (!t1) 
      return t2;
    if (!t2) 
      return t1;

    TreeNode* node = new TreeNode(t1->val + t2->val);
    node->left = mergeTrees(t1->left, t2->left);
    node->right = mergeTrees(t1->right, t2->right);
    return node;
}

//#################################### Preorder traersal with new Tree  #################################### 
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    if ( t1 && t2 ) {
        TreeNode * root = new TreeNode(t1->val + t2->val);
        root->left = mergeTrees(t1->left, t2->left);
        root->right = mergeTrees(t1->right, t2->right);
        return root;
    } else {
        return t1 ? t1 : t2;
    }
}

//#################################### More Expanded version #################################### 
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) { 
  if(t1 == NULL && t2 == NULL) return NULL;
  else if(t1 != NULL && t2 == NULL) return t1;
  else if(t1 == NULL && t2 != NULL) return t2;
  else t1->val = t1->val + t2->val;
  t1->left = mergeTrees(t1->left, t2->left);
  t1->right = mergeTrees(t1->right, t2->right);
  return t1;
}

//#################################### #################################### 
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) { 
  if (!t1 && !t2) { 
    return nullptr; 
  }
  TreeNode* node = new TreeNode((t1 ? t1->val : 0) + (t2 ? t2->val : 0));
  node->left = mergeTrees((t1 ? t1->left : nullptr), (t2 ? t2->left : nullptr));
  node->right = mergeTrees((t1 ? t1->right : nullptr), (t2 ? t2->right : nullptr));
  return node;
}

//#################################### Pytonic #################################### 
//
//class Solution(object):
//    def mergeTrees(self, t1, t2):
//        if t1 and t2:
//            root = TreeNode(t1.val + t2.val)
//            root.left = self.mergeTrees(t1.left, t2.left)
//            root.right = self.mergeTrees(t1.right, t2.right)
//            return root
//        else:
//            return t1 or t2
//
//class Solution(object):
//    def mergeTrees(self, t1, t2):
//        """
//        :type t1: TreeNode
//        :type t2: TreeNode
//        :rtype: TreeNode
//        """
//        if not t1 and not t2: return None
//        if t1:
//            v1, L1, R1 = t1.val, t1.left, t1.right
//        else:
//            v1, L1, R1 = 0, None, None
//        if t2:
//            v2, L2, R2 = t2.val, t2.left, t2.right
//        else:
//            v2, L2, R2 = 0, None, None
//        node = TreeNode(v1+v2)
//        node.left = self.mergeTrees(L1, L2)
//        node.right = self.mergeTrees(R1, R2)
//        return node
//
//
