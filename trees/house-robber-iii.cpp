//House Robber III
//The thief has found himself a new place for his thievery again. There is only
//one entrance to this area, called the "root." Besides the root, each house
//has one and only one parent house. After a tour, the smart thief realized
//that "all houses in this place forms a binary tree". It will automatically
//contact the police if two directly-linked houses were broken into on the same
//night.
//Determine the maximum amount of money the thief can rob tonight without
//alerting the police.
//Example 1:
//     3
//    / \
//   2   3
//    \   \
//     3   1
//Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
//Example 2:
//     3
//    / \
//   4   5
//  / \   \
// 1   3   1
//Maximum amount of money the thief can rob = 4 + 5 = 9.

//############################### Recursive ###############################
int rob(TreeNode* root) {
  if (root == nullptr)
   return 0;
  int val = 0;
  if (root->left != nullptr) {
    val += rob(root->left->left) + rob(root->left->right); //pick first level LEFT tree node
  }
  if (root->right != nullptr) {
      val += rob(root->right->left) + rob(root->right->right); //pick first level RIGHT tree node
  }
  return max(val + root->val, rob(root->left) + rob(root->right)); // get the max between root+first level and left+right subtree
}

//################## store cost of single node only ##################
int robHelper(TreeNode* root,unordered_map<TreeNode*,int>& umap) {
  if (root == nullptr)
   return 0;
  if (umap.count(root))
   return umap[root];
  int val = 0 ;
  if (root->left != nullptr) {
      val += robHelper(root->left->left, umap) + robHelper(root->left->right, umap);
  }
  if (root->right != nullptr) {
      val += robHelper(root->right->left, umap) + robHelper(root->right->right, umap);
  }

  val = max(val + root->val, robHelper(root->left, umap) + robHelper(root->right, umap));
  umap[root] = val;
  return val;
}

int rob(TreeNode* root) {
  unordered_map<TreeNode*,int> umap;
  return robHelper(root,umap);
}

//############################### DFS solution + store the cost of 2 nodes ###############################
//res[0] = max Money allowing root to be stolen
//res[1] = max Money avoiding root itself
vector<int> dfs(TreeNode* x) {
  if (!x)  {
    return {0,0};
  }
  vector<int> left = dfs(x->left);
  vector<int> right = dfs(x->right);
  vector<int> res {0,0};
  res[0] = left[1] + right[1] + x->val;
  res[1] = max(left[0], left[1]) + max(right[0], right[1]);
  return res;
}
int rob(TreeNode* root) {
  vector<int> num = dfs(root);
  return max(num[0], num[1]);
}
