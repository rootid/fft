//Write a function that returns true if the given Binary Tree is SumTree else false. A SumTree is a Binary Tree where the value of a node is equal to sum of the nodes present in its left subtree and right subtree
//
//
//Time complexity : DFS search : O(n)  n : Total #of vertex
//Space complexity : stack length O(l) : l height of a bin tree

#include<iostream>

using namespace std;

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int val;
    TreeNode (int aVal) : val(aVal),left(NULL),right(NULL) {

    }
};


//int isSumTreeHelper (TreeNode *root) {
//    if(!root)  {
//      return 0;
//    } 
//    return ( root->val + isSumTreeHelper(root->left) + 
//            isSumTreeHelper(root->right) );
//}


int isSumTreeHelper_0 (TreeNode *root) {
    if(!root)  {
      return 0;
    } 
    int ltSum = isSumTreeHelper(root->left);
    int rtSum = isSumTreeHelper(root->right);
    if ( root->val == ltSum + rtSum ) {
        int tmp_ = root->val + ltSum + rtSum;
        cout << "sum = " << tmp_ << endl;
        return ( root->val + ltSum + rtSum);
    } else {
        cout << "got -1" << endl;
        return -1;
    }
}

bool isSumTree (TreeNode *root) {
  
    if (!root) {
      return true;
    } else if ( root->val == ( isSumTreeHelper_0 (root->left) + isSumTreeHelper_0 (root->right) ) ) {
      return true;
    } else {
      return false;
    }

}

int main() {

  //TreeNode *t;
  //TreeNode *t = new TreeNode(26);
  TreeNode *t = new TreeNode(32);
  t->left = new TreeNode(10);
  t->left->left = new TreeNode(4);
  t->left->right = new TreeNode(6);
  t->left->right->right = new TreeNode(3);
  t->right = new TreeNode(3);
  t->right->right= new TreeNode(3);
  t->right->right->right = new TreeNode(3);

  if ( true == isSumTree (t) )  {
    cout << "SumTree available" << endl;
  } else {
    cout << "SumTree not available" << endl;
  }

}


