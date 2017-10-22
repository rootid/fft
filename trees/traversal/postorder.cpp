//Binary Tree Postorder Traversal
//Given a binary tree, return the postorder traversal of its nodes' values.
//
//For example:
//Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
//return [3,2,1].
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


//postorder(node)
//  if (node = null)
//    return
//  postorder(node.left)
//  postorder(node.right)
//  visit(node)
//
//
 
//iterativePostorder(node)
//  s ← empty stack
//  lastNodeVisited ← null
//  while (not s.isEmpty() or node ≠ null)
//    if (node ≠ null)
//      s.push(node)
//      node ← node.left
//    else
//      peekNode ← s.peek()
//      // if right child exists and traversing node
//      // from left child, then move right
//      if (peekNode.right ≠ null and lastNodeVisited ≠ peekNode.right)
//        node ← peekNode.right
//      else
//        visit(peekNode)
//        lastNodeVisited ← s.pop()

//######################################### PostOrder with Stack ######################################### 
public List<Integer> postorderTraversal(TreeNode root) {
    TreeNode lastVisitedNode = null;
    TreeNode pkNode = null;
    List<Integer> lst = new LinkedList<>();
    Stack<TreeNode> tStack = new Stack<>();
    while(!tStack.isEmpty() || root != null) {
        if(root != null) {
            tStack.push(root);
            root = root.left;
        } else {
            pkNode = tStack.peek();
            if(pkNode.right != null && lastVisitedNode != pkNode.right) {
                  root = pkNode.right;
            } else {
                lastVisitedNode = pkNode;
                lst.add(pkNode.val);
                tStack.pop();
            }
        }
        
    }
    return lst;
}

//######################################### PostOrder with Stack ######################################### 
vector<int> postorderTraversal(TreeNode* root) {
  
  stack<TreeNode*> s;
  vector<int> result;
  TreeNode *t = root;
  TreeNode *visited = NULL;
  while(!s.empty() || t != NULL) {
    if(t != NULL) {
      s.push(t);
      t = t->left;
    } else {
      //Move to right
      TreeNode *tmp = s.top();
      if(tmp->right && tmp->right != visited) {   //{1,#,2,3,#,5}
        t = tmp->right;
      } else {
        //cout << "V = " << tmp->val << endl;
        result.push_back(tmp->val);
        visited = s.top();
        s.pop();
      }
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

  postorderTraversal(t);
}
