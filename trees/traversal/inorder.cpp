//Binary Tree Inorder Traversal
//Given a binary tree, return the inorder traversal of its nodes' values.
//For example:
//Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
//return [1,3,2].
//
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//inorder(node)
//  if (node = null)
//    return
//  inorder(node.left)
//  visit(node)
//  inorder(node.right)
//

//iterativeInorder(node)
//  s ← empty stack
//  while (not s.isEmpty() or node ≠ null)
//    if (node ≠ null)
//      s.push(node)
//      node ← node.left
//    else
//      node ← s.pop()
//      visit(node)
//      node ← node.right


//######################################### Inorder traversal  with Stack ######################################### 
public List<Integer> inorderTraversal(TreeNode root) {
    List<Integer> lst = new LinkedList<>();
    Stack<TreeNode> stk = new Stack<>();
    while(!stk.isEmpty() || root != null) {
        if(root != null) {
            stk.push(root);
            root = root.left;
        } else {
            root =  stk.pop();
            lst.add(root.val);
            root = root.right;
        }
    }
    return lst;
}

//######################################### Inorder traversal  ######################################### 
vector<int> inorderTraversal(TreeNode* root) {
  
  stack<TreeNode*> s;
  vector<int> result;
  TreeNode *t = root;
  while(!s.empty() || s != null) {
    if(t) { 
      s.push(t)
      t = t->left;
    } else {
      t = s.top();
      result.push_back(t->val);
      s.pop();
      t = t->right;
    }
  }
  return result;

}

int main() {

  TreeNode* t = new TreeNode(1);
  t->right = new TreeNode(2);
  t->right->left = new TreeNode(3);

  inorderTraversal(t);
}
