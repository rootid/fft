//Invert Binary Tree 
//
//     4
//   /   \
//  2     7
// / \   / \
//1   3 6   9
//  to
//     4
//   /   \
//  7     2
// / \   / \
//9   6 3   1
//
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//######################################### Recursion ######################################### 
public TreeNode invertTree(TreeNode root) {
     if(root != null) {
     TreeNode tmp = invertTree(root.left);
     root.left = invertTree(root.right);
     root.right = tmp;
  }
  return root;
}

//EXample use of pointer and referene
//
//NOTE : in this recursion we need to return the parent
//WRONG way
TreeNode* invertTree(TreeNode* root) {
     if(root) {
         TreeNode* l = invertTree(root->left);
         TreeNode *r = invertTree(root->right);
         TreeNode *tmp = l;
         l = r;
         r = tmp;
     }
     return root;
}

TreeNode* invertTree(TreeNode* root) {
     if(root) {
         TreeNode* tmp = invertTree(root->left);
         root->left = invertTree(root->right);
         root->right = tmp;
     }
     return root;
}

//With stack : It is just about the traversal + swap
//######################################### Stack ######################################### 
TreeNode* invertTree(TreeNode* root) {
  if(!root) {
    return root;
  }
  stack<TreeNode*>  stk;
  stk.push(root);
  while(!stk.empty()) {
    TreeNode *tmp = stk.top();
    stk.pop();
    if(tmp) {
      swap(tmp->left,tmp->right);
      stk.push(tmp->left);
      stk.push(tmp->right);
    }
  }
  return root;
}

//######################################### Queue  ######################################### 
TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return root;
        queue<TreeNode *>q;
        TreeNode *temp, *cur;
        q.push(root);
        while (!q.empty()) {
            cur = q.front();
            q.pop();
            temp = cur->left;
            cur->left = cur->right;
            cur->right = temp;
            if (cur->left != NULL)
                q.push(cur->left);
            if (cur->right != NULL)
                q.push(cur->right);
        }
        return root;
}

int main() {
  TreeNode* t = new TreeNode(1);
  t->left = new TreeNode(2);
  t->right = new TreeNode(3);
  t->right->left = new TreeNode(5);
  t->right->right = new TreeNode(7);
  binaryTreePaths(t);
}
  
