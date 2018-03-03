//Find Mode in Binary Search Tree
//Given a binary search tree (BST) with duplicates, find all the mode(s) (the
//most frequently occurred element) in the given BST.
//Assume a BST is defined as follows:
//The left subtree of a node contains only nodes with keys less than or equal
//to the node's key.
//The right subtree of a node contains only nodes with keys greater than or
//equal to the node's key.
//Both the left and right subtrees must also be binary search trees.
//For example:
//Given BST [1,nullptr,2,2],
//   1
//    \
//     2
//    /
//   2
//return [2].
//Note: If a tree has more than one mode, you can return them in any order.
//Follow up: Could you do that without using any extra space? (Assume that the
//implicit stack space incurred due to recursion does not count).
//############################################# O(K) space #############################################

//1. keep track of the previous node to identify when the current node's value
//is different from previous node's value.
//2. When the values of both nodes are different, update max frequency if
//occurrence of current value is greater.
//3. Only push the value with an occurrence equal to max frequency


vector<int> findMode(TreeNode* root) {
  vector<int> ans;
  if(!root) return ans;
  int max_freq = 1, cnt = 1;
  TreeNode *prev = NULL;
  helper(root, ans, max_freq, prev, cnt);
  if(cnt == max_freq) {
    ans.push_back(prev->val);
  }
  return ans;
}
private:
void helper(TreeNode *root, vector<int> &ans, int &max_freq, TreeNode *&prev, int &cnt) {
  if(!root) return;
  helper(root->left, ans, max_freq, prev, cnt);
  if(prev && prev->val == root->val) {
      if(++cnt > max_freq) {
        ans.clear();
        max_freq = cnt;
      }
  } else if(prev && prev->val != root->val) {
      if(cnt == max_freq) {
        ans.push_back(prev->val);
      }
      cnt = 1; //reset the current counter
  }
  prev = root;
  helper(root->right, ans, max_freq, prev, cnt);
}
//############################################# NEEDS TO FIX #############################################
vector<int> findMode(TreeNode root) {
    int maxFreq = 0, curFreq = 0;
    TreeNode* prev = NULL;
    vector<int> ans;
    traverse(prev,root,curFreq,maxFreq,ans);
    return ans;
}

void traverse(TreeNode* prev,TreeNode* root,int& curFreq,int &maxFreq,vector<int>& ans) {
  if (root == nullptr) {
    return;
  }
  //inorder traversal
  traverse(prev,root->left,curFreq,maxFreq,ans);
  if (prev != nullptr && root->val == prev->val) {
    curFreq++;
  } else {
    curFreq = 1;
  }
  if (curFreq >= maxFreq) {
    maxFreq = curFreq;
    ans.push_back(root->val);
  }
  prev = root;
  traverse(prev,root->right,curFreq,maxFreq,ans);
}
//############################### O (n) T and O(n) ###############################
vector<int> findMode(TreeNode* root) {
  unordered_map<int, int> map;
  vector<int> result;
  int modeCount = getModeCount(root, map);
  for(pair<int,int> p : map) {
      if(p.second == modeCount) {
          result.push_back(p.first);
      }
  }
  return result;
}
//Traverse the tree using depth first search.
//Return the mode count (i.e. The count of a repeated number that occurs the
//most.) of the tree.
int getModeCount(TreeNode* root, unordered_map<int, int> &map) {
    if(root == NULL)
        return 0;
    if(map.find(root->val) == map.end()) {
        map.insert(pair<int, int>(root->val, 1));
    } else {
        map[root->val]++;
    }
    return max(map[root->val], max(getModeCount(root->left, map), getModeCount(root->right, map)));
}
