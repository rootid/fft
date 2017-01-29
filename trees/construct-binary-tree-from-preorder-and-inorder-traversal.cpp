//TODO :
//Given preorder and inorder traversal of a tree, construct the binary tree.
//Note:
//You may assume that duplicates do not exist in the tree.

  TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int l, int r, int ll, int rr) {
        if (l >= r)
            return NULL;
        TreeNode* cur = new TreeNode(preorder[l]);
        if (l == r - 1)
            return cur;
        int index_root = mp[preorder[l]], l_size;
        l_size = index_root - ll;
        cur->left = helper(preorder, inorder, l + 1, l + 1 + l_size, ll, index_root);
        cur->right = helper(preorder, inorder, l + 1 + l_size, r, index_root + 1, rr);
        return cur;
    }
    unordered_map<int, int> mp;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty())
            return NULL;
        for (int i = 0; i < inorder.size(); i++)
            mp[inorder[i]] = i;
        return helper(preorder, inorder, 0, preorder.size(), 0, inorder.size());
    }


 unordered_map<int, int> um; // map inorder[i] to i
    TreeNode* dfs(vector<int>& preorder, int pleft, int pright, vector<int>& inorder, int ileft, int iright) {
        if(pleft > pright || ileft > iright) return nullptr;
        int root_val = preorder[pleft]; // leftmost element in preorder is the root node
        TreeNode* root = new TreeNode(root_val);
        
        int root_idx = um[root_val]; // root index in inorder
        int nleft = root_idx - ileft; // size of left sub-tree
        root->left = dfs(preorder, pleft+1, pleft + nleft, inorder, ileft, root_idx - 1);
        root->right = dfs(preorder, pleft + nleft + 1, pright, inorder, root_idx + 1, iright);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size(), i = 0;
        for(int val : inorder) um[val] = i ++;
        return dfs(preorder, 0, n-1, inorder, 0, n-1);
    }


struct TreeNode *buildTree(int *preorder, int *inorder, int n) {
    if(n == 0)
        return NULL;
    
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    
    int rootIndex;
    for(rootIndex=0; inorder[rootIndex] != root->val; ++rootIndex);
    
    root->left = rootIndex == 0 ? NULL : buildTree(preorder+1, inorder, rootIndex);
    
    root->right = rootIndex == n-1 ? NULL : buildTree(preorder+rootIndex+1, inorder+rootIndex+1, n-rootIndex-1);
    
    return root;
}
