//TODO :
//Given inorder and postorder traversal of a tree, construct the binary tree.
//Note:
//You may assume that duplicates do not exist in the tree.
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



public TreeNode buildTree(int[] inorder, int[] postorder) {
    return buildTree(inorder, 0, inorder.length, postorder, 0, postorder.length);
}

private static TreeNode buildTree(int[] inorder, int inStart, int inEnd, int[] postorder, int postStart, int postEnd) {
    if (postStart == postEnd) {
        return null;
    }
    int rootVal = postorder[postEnd - 1];
    int inRoot = -1;
    for (int i = inStart, j = inEnd - 1; i <= j; ++i, --j) {
        if (inorder[i] == rootVal) {
            inRoot = i;
            break;
        } else if (inorder[j] == rootVal) {
            inRoot = j;
            break;
        }
    }
    if (inRoot == -1) {
        throw new IllegalArgumentException("Only in postorder: " + rootVal);
    }
    TreeNode root = new TreeNode(rootVal);
    root.left = buildTree(inorder, inStart, inRoot, postorder, postStart, postStart + (inRoot - inStart));
    root.right = buildTree(inorder, inRoot + 1, inEnd, postorder, postStart + (inRoot - inStart), postEnd - 1);
    return root;
}

//####################################### With Stack ####################################### 
TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) { 
  if(inorder.size() == 0) { 
    return NULL; 
  }
  TreeNode *p;
  TreeNode *root;
  stack<TreeNode *> stn;
  root = new TreeNode(postorder.back()); 
  stn.push(root); 
  postorder.pop_back(); 
  while(!stn.empty()) {
      //left substree
      if(inorder.back() == stn.top()->val) {
          p = stn.top();
          stn.pop(); 
          inorder.pop_back(); 
          if(inorder.size() == 0) {
            break;
          }
          //check for all next matching elements
          if(stn.size() && inorder.back() == stn.top()->val)
              continue;
          p->left = new TreeNode(postorder.back()); 
          stn.push(p->left);
          postorder.pop_back();
      } else {
        //Right subtree
          p = new TreeNode(postorder.back());
          stn.top()->right = p; 
          stn.push(p); 

          postorder.pop_back();
      }
  }
  return root;
}

//######################################## Recursion NEED TO FIX ######################################## 
TreeNode* helper(vector<int>& inorder, vector<int>& postorder, int n) {
    if(n == 0) {
        return NULL;
    }
    TreeNode *root = new TreeNode(postorder[n-1]); 
    int rootIndex;
    //search 
    //TODO : use unordered_map
    for(rootIndex=0; inorder[rootIndex] != root->val; ++rootIndex);
    vector<int>post(postorder.begin(),postorder.end()+rootIndex);
    vector<int>nino1(inorder.begin(),inorder.end()-rootIndex);
    root->left = rootIndex == 0 ? NULL : helper(nino1,post,rootIndex);
    cout << rootIndex << endl;
    vector<int>npost(postorder.begin()+rootIndex,postorder.end());
    vector<int>nino(inorder.begin()+rootIndex,inorder.end());
    n = 
    root->right = rootIndex == n-1 ? NULL : helper(nino,npost,n-1-rootIndex);
    return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
  int n = postorder.size();
  return helper(inorder,postorder,n);
}
//######################################### Recursion ######################################### 
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

//############################################# Recursion  ############################################# 
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return helper(inorder,0,inorder.size(),postorder,0,postorder.size());
}
TreeNode* helper(vector<int>& inorder,int i,int j,vector<int>& postorder,int ii,int jj) {
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
