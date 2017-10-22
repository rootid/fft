//Binary Tree Preorder Traversal
//Given a binary tree, return the preorder traversal of its nodes' values.
//For example:
//Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
//return [1,2,3].

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


//preorder(node)
//  if (node = null)
//    return
//  visit(node)
//  preorder(node.left)
//  preorder(node.right)

//iterativePreorder(node)
//s ← empty stack
//while (not s.isEmpty() or node ≠ null)
//  if (node ≠ null)
//    visit(node)
//    if (node.right ≠ null)
//      s.push(node.right)
//    node ← node.left
//  else
//    node ← s.pop()

//######################################### Preorder ######################################### 
public List<Integer> preorderTraversal(TreeNode root) {
    Stack<TreeNode> stk = new Stack();
    List<Integer> lst = new LinkedList<>();
    while(!stk.isEmpty() || root != null) {
        if(root != null) {
            lst.add(root.val);
            if(root.right != null) {
                stk.push(root.right); // Preorder right pointers
            }
            root = root.left;
        } else {
            root = stk.pop();
        }    
    }
    return lst;
}

//######################################### Preorder ######################################### 
vector<int> preorderTraversal(TreeNode* root) {
  //Store the right substree for next visit and traverse the left substree 
  stack<TreeNode*> s;
  vector<int> result;
  TreeNode *t = root;
  while(!s.empty() || t != NULL) {
    if(t != NULL) {
      //cout << "N = " << t->val << endl;
      result.push_back(t->val);
      if(t->right) {
        s.push(t->right);
      }
      t = t->left;
    } else {
      t = s.top();
      s.pop();
    }
  }
  return result;
}

int main() {

  TreeNode* t = new TreeNode(3);
  //t->right = new TreeNode(2);
  //t->right->left = new TreeNode(3);

  t->left  = new TreeNode(1);
  t->right = new TreeNode(2);

  preorderTraversal(t);
}
