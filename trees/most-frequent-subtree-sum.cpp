//Most Frequent Subtree sum
//Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.
//Examples 1
//Input:
//  5
// /  \
//2   -3
//return [2, -3, 4], since all the values happen only once, return all of them in any order.
//Examples 2
//Input:
//  5
// /  \
//2   -5
//return [2], since 2 happens twice, however -5 only occur once.
//Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
//####################################################### Postorder traversal  ####################################################
int countSubtreesums(TreeNode *r, unordered_map<int,int> &counts, int& maxCount){ 
  if(r == nullptr) 
    return 0;
  int sum = r->val; 
  sum += countSubtreesums(r->left, counts, maxCount);
  sum += countSubtreesums(r->right, counts, maxCount);
  ++counts[sum];
  maxCount = max(maxCount, counts[sum]);
  return sum;
}
vector<int> findFrequentTreesum(TreeNode* root) { 
  unordered_map<int,int> counts;
  int maxCount = 0;
  countSubtreesums(root, counts, maxCount);
  vector<int> maxsums;
  for(const auto& x :  counts){
      if(x.second == maxCount) {
        maxsums.push_back(x.first);
      }
  }
  return maxsums;
}

//####################################################### Inorder traversal  ####################################################
bool inorder_helper(TreeNode *root,int &sum,int &max_count,unordered_map<int,int>& freq_map) {
    if(root == NULL) {
        return false;
    }
    if(root->left == NULL && root->right == NULL) {
        freq_map[root->val]++;
        sum += root->val;
        max_count = max(max_count,freq_map[root->val]);
        return true;
    }
    int sum1 = 0, sum2 = 0;
    bool b1 = inorder_helper(root->left,sum1,max_count,freq_map);
    bool b2 = inorder_helper(root->right,sum2,max_count,freq_map);
    if(b1) {
        sum += sum1;
    }
    if(b2) {
        sum += sum2;
    }
    sum+= root->val;
    freq_map[sum]++;
    max_count = max(max_count,freq_map[sum]);
    return (true);
}
vector<int> findFrequentTreeSum(TreeNode* root) {
   int sum = 0;
   int max_count = 0;
   unordered_map<int,int> freq_map;
   inorder_helper(root,sum,max_count,freq_map);
   vector<int> rlist;
   for(auto &f : freq_map) {
       if(f.second == max_count) {
           rlist.push_back(f.first);
       }
   }
   return (rlist);
}
    
