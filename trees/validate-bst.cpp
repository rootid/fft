//Validate Binary Search Tree
//
//Given a binary tree, determine if it is a valid binary search tree (BST).
//Assume a BST is defined as follows:
//The left subtree of a node contains only nodes with keys less than the node's
//key.
//The right subtree of a node contains only nodes with keys greater than the
//node's key.
//Both the left and right subtrees must also be binary search trees.
//

#include<iostream>
#include<stdlib.h>
#include<limits.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


//######################################### Inorder traversal #########################################
   private TreeNode prev; //With class variable
   private boolean isValidBSTHelper(TreeNode root) {
       if(root == null) return true;
       if(!isValidBSTHelper(root.left)) return false;
       if(prev != null && prev.val >= root.val) return false;
       prev = root;
       return isValidBSTHelper(root.right);
   }
   public boolean isValidBST(TreeNode root) {
       return isValidBSTHelper(root);
   }

//######################################### min,max  #########################################
    public boolean isValidBST(TreeNode root) {
        return isValidBST(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }

    public boolean isValidBST(TreeNode root, long minVal, long maxVal) {
        if (root == null) return true;
        if (root.val >= maxVal || root.val <= minVal) return false;
		//Right : update min val while traversing to right node
        return isValidBST(root.left, minVal, root.val) && isValidBST(root.right, root.val, maxVal);
    }

//######################################### Inorder traversal  #########################################
bool bstValidCheckHelper(TreeNode* root,TreeNode*& prev) {

  if(!root) return true;
  if (!bstValidCheckHelper(root->left,prev) ) return false;
  if(prev != NULL && prev->val >= root->val) return false;
  prev = root;
  return (bstValidCheckHelper(root->right,prev) );
}

bool isValidBST(TreeNode* root) {
  TreeNode *prev = NULL;
  return bstValidCheckHelper(root,prev);
}



int main() {

  //{3,1,9,#,#,2,15} : invalid
  //{3,1,9,#,#,4,15} : valid
  TreeNode* t = new TreeNode(3);
  t->left = new TreeNode(1);
  t->right = new TreeNode(9);
  //t->right->left = new TreeNode(4);
  t->right->left = new TreeNode(2);
  t->right->right = new TreeNode(15);
  //t->right = new TreeNode(2);
  //t->right->right = new TreeNode(3);
  //t->left->right = new TreeNode(3);
  ////t->left->left = new TreeNode(3);
  ////t->left->right = new TreeNode(4);
  ////t->right->left = new TreeNode(4);
  ////t->right->right = new TreeNode(3);
  if ( true == isValidBST(t) ) {
    cout << "IS VALID " << endl;
  } else {

    cout << "NOT VALID " << endl;
  }

}
