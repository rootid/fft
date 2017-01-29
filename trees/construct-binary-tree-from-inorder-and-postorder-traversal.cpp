//TODO :
//Given inorder and postorder traversal of a tree, construct the binary tree.
//Note:
//You may assume that duplicates do not exist in the tree.

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
     TreeNode *root = buildTree();
}


//       13
//     /    \
//    2      3
//   / \    /
//  5   6  7
//        / \
//       8   9
//            \
//            10
//            /
//          12
//
//5,  2,  6,  13,  8,  7,  9,  12,  10,  3
//---left--- root  ---------right---------
//
//5,  6,  2,  8,  12,  10,  9,  7,  3,  13
//---left---	---------right---------- root 


       unordered_map<int, int> inm; // inorder map [inorder[i], i]

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size(), i = 0;
        for(auto val: inorder) inm[val] = i++; // build inm for dfs 
        
        return dfs(inorder, 0, n - 1, postorder, 0, n - 1);
    }
    
    TreeNode* dfs(vector<int>& inorder, int ileft, int iright, vector<int>& postorder, int pleft, int pright) {
        if(ileft > iright) return nullptr;
        
        int val = postorder[pright]; // root value
        TreeNode *root = new TreeNode(val);
        if(ileft == iright) return root;
        
        int iroot = inm[val];
        int nleft = iroot - ileft; // length of left subtree
        root->right = dfs(inorder, iroot + 1, iright, postorder, pleft + nleft, pright - 1);
        root->left = dfs(inorder, ileft, iroot - 1, postorder, pleft, pleft + nleft - 1);
        
        return root;
    }


unordered_map<int, int> um; // map inorder[i] to i
TreeNode* dfs(vector<int>& inorder, int ileft, int iright, vector<int>& postorder, int pleft, int pright) {
    if(ileft > iright || pleft > pright) return nullptr;
    int val = postorder[pright]; // last element in postorder is the root node
    TreeNode* root = new TreeNode(val);
    int root_idx = um[val]; // root index in inorder
    int nleft = root_idx - ileft; // size of left sub-tree
    root->left = dfs(inorder, ileft, root_idx-1, postorder, pleft, pleft + nleft - 1);
    root->right = dfs(inorder, root_idx+1, iright, postorder, pleft + nleft, pright - 1);
    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int n = inorder.size(), i = 0;
    for(int val : inorder) um[val] = i++;
    return dfs(inorder, 0, n-1, postorder, 0, n-1);
}

//############################ Iterative vversion ############################ 
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    vector<TreeNode*> parent;
    TreeNode *prev = nullptr;
    int i = 0, j = 0, n = inorder.size();
    while(j < n) {
        while(!parent.empty() && postorder[j] == parent.back() -> val) {
            parent.back()->right = prev;
            prev = parent.back();
            parent.pop_back();
            j++;
        }
        if(i < n) {
            parent.push_back(new TreeNode(inorder[i++]));
            parent.back() -> left = prev;
            prev = nullptr;
        }
    }
    return prev;
}



//find(inorder.begin() + i,inorder.begin() + j,mid);
//to
//lower_bound(inorder.begin() + i,inorder.begin() + j,mid);
//since inOrder array is in order, can use binary search.
 TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        
        return helper(inorder,0,inorder.size(),postorder,0,postorder.size());
    }
private:
    TreeNode* helper(vector<int>& inorder,int i,int j,vector<int>& postorder,int ii,int jj)
    {
        // 每次取postorder的最后一个值mid，将其作为树的根节点
        // 然后从inroder中找到mid，将其分割成为两部分，左边作为mid的左子树，右边作为mid的右子树
        // tree:     8 4 10 3 6 9 11
        // Inorder   [3 4 6] 8 [9 10 11]
        // postorder [3 6 4]   [9 11 10] 8

        if(i >= j || ii >= jj)
            return NULL;
        
        int mid = postorder[jj - 1];
        
        auto f = find(inorder.begin() + i,inorder.begin() + j,mid);
        
        int dis = f - inorder.begin() - i;
        
        TreeNode* root = new TreeNode(mid);
        root -> left = helper(inorder,i,i + dis,postorder,ii,ii + dis);
        root -> right = helper(inorder,i + dis + 1,j,postorder,ii + dis,jj - 1);
        
        return root;
        
    }
