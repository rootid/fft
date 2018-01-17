#include "../headers/global.hpp"
#include "../headers/treenode.h"


TreeNode* helper(vector<int>& inorder, vector<int>& postorder, int n) {
    cout << "inorder = "  << inorder.size()  << " postorder" << postorder.size() << endl;
    if(n == 0) {
        return NULL;
    }
    TreeNode *root = new TreeNode(postorder[n-1]); 
    int rootIndex;
    for(rootIndex=0; inorder[rootIndex] != root->val && rootIndex < inorder.size() ; rootIndex++);
    cout << "rootIndex = " << rootIndex  << " v = " << inorder[rootIndex]<< endl;
    vector<int>lpost(postorder.begin()+rootIndex,postorder.end());
    vector<int>lin(inorder.begin(),inorder.end()-rootIndex);
    n = lin.size();
    cout << "left n = " << n << endl;
    root->left = rootIndex == 0 ? NULL : helper(lin,lpost,n);
    cout << "invoking right " << n << endl;
    vector<int>rpost(postorder.begin()+rootIndex,postorder.end());
    vector<int>rin(inorder.begin()+rootIndex,inorder.end());
    n = rin.size();
    cout << "right n = " << n << endl;
    root->right = rootIndex == 0 ? NULL : helper(rin,rpost,n);
    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
  int n = postorder.size();
  return helper(inorder,postorder,n);
}

int main() {
  vector<int> inorder{2,1,3};
  vector<int> postorder{2,3,1};
  buildTree(inorder,postorder);
  //[2,1]
  //[2,1]
  //expected : [1,2]
}
