//Kth Smallest Element in a BST
//Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
//Note: 
//You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
//Follow up:
//What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
//Hint:
//Try to utilize the property of a BST.
//What if you could modify the BST node's structure?
//The optimal runtime complexity is O(height of BST).
#include<iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


//Try the left subtree first. If that made k zero, then its answer is the overall answer and we return it right away. Otherwise, decrease k for the current node, and if that made k zero, then we return the current node's value right away. Otherwise try the right subtree and return whatever comes back from there.
int kthSmallestHelper(TreeNode* root, int k,int& l) {
  if(root) {
    int lval = kthSmallestHelper(root->left,k,l);
    cout <<  "L = " << l << " V = " << root->val << endl;
    //l = l + 1;
    if(l == k) {
      return lval; //verifying left subtree
    } else {
      l = l + 1;
      if(l == k) {
        return root->val; //verifying right subtree
      } else {
        int rval = kthSmallestHelper(root->right,k,l);
      }
    }
  }
  //cout <<  "L = " << l << " V = " << root->val << endl;
}

int find(TreeNode* root, int& k) {
    if (root) {
        int x = find(root->left, k);
        //return !k ? x : !--k ? root->val : find(root->right, k);
        if (!k) {
          return x;
        } else { 
          if(!--k) { 
              return root->val;
          } else  {
              find(root->right, k);
          }
        }
    }
}

int kthSmallest(TreeNode* root, int k) {
  int l = 0;
  return kthSmallestHelper(root,k,l);
  //return find(root,k);
}

int main(int argc, char *argv[])
{
  TreeNode* t = new TreeNode(20);
  t->left = new TreeNode(10);
  t->left->left = new TreeNode(5);
  t->left->right = new TreeNode(15);
  t->left->right->right = new TreeNode(17);
  t->right = new TreeNode(60);

  int sum = 4;
  int r = kthSmallest(t,sum);
  cout << "smallest ele " << r << endl;
  return 0;
}


//Contrainted inorder traversal with MAX k memory location instead of stack

//Solution 2, C++ with circular vector
//Using a vector of fixed size k and a stack pointer i into it which will be used modulo k.

int kthSmallest(TreeNode* root, int k) {
    vector<TreeNode*> stac(k);
    int i = 0, j = k;
    while (true) {
        while (root) {
            stac[i++%k] = root;
            root = root->left;
        }
        root = stac[--i%k];
        if (! --j)
            return root->val;
        root = root->right;
    }
}


//Solution 3, C++ with deque
//I really like the previous version, but the fixed size k isn't always necessary, so here's a version using a deque:

int kthSmallest(TreeNode* root, int k) {
    deque<TreeNode*> stac;
    while (true) {
        while (root) {
            stac.push_front(root);
            while (stac.size() > k)
                stac.pop_back();
            root = root->left;
        }
        root = stac.front();
        stac.pop_front();
        if (! --k)
            return root->val;
        root = root->right;
    }


//ANS : with morris traversal
//https://leetcode.com/discuss/43299/o-k-space-o-n-time-10-short-lines-3-solutions?show=43556#a43556
