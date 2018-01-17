// Binary Search Tree Iterator
//Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
//Calling next() will return the next smallest number in the BST.
//Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
#include "../headers/global.hpp"
#include "../global/treenode.h"

//######################################### With Stack ######################################### 
Class Solution {
    Stack<TreeNode> stk;

    public BSTIterator(TreeNode root) {
        stk = new Stack<>();
        pushAll(root);
    }

    /** @return whether we have a next smallest number */
    public boolean hasNext() {
        return !stk.isEmpty();
    }

    /** @return the next smallest number */
    public int next() {
        int val = -1;
        if(hasNext()) {
            TreeNode tmp = stk.pop();
            val = tmp.val;
            pushAll(tmp.right);
        }
        return val;
    }
    
    
    private void pushAll(TreeNode root) {
        while(root != null) { 
            stk.push(root);
            root = root.left;
        }
    }
}

//################# W/O modifying the actual struct ###########
class BSTIterator {
private :
    stack<TreeNode*> st;
    //L->D->R (inorder)
public:
    
    BSTIterator(TreeNode *root) {
        push_all(root);
    }
    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(st.empty())  {
            return false;
        }  
        return true;
    }
    /** @return the next smallest number */
    int next() {
        TreeNode* tmp = st.top();
        st.pop();
        if(tmp->right) {
            push_all(tmp->right);
        }
        return tmp->val;
    }
    
    void push_all(TreeNode *tmp) {
         while(tmp) {
            st.push(tmp);
            tmp = tmp->left;
        }
    }
};
//################# modifying the actual struct ###########
/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
BSTIterator(TreeNode* root) {
    TreeNode* head = NULL;
    TreeNode* pre = NULL;
    convert(root,pre,head);
}
void convert(TreeNode* root,TreeNode* pre,TreeNode* head) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL){
        convert(root->left,pre,head);
    }
    if (head == NULL) {
        head = root;
    }
    if (pre == NULL) {
        pre = root;
    } else {
        pre->right = root;
        pre = root;
    }
    if (root->right != NULL) {
        convert(root->right,pre,head);
    }
}
boolean hasNext() { 
  return head != NULL;
}
    
int next() {
    if (hasNext()) {
      TreeNode* t = head;
      head = head->right;
      return t->val; 
    } else {
        return -1;
    }
}
 
