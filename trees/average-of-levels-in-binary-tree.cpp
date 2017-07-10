//Average of Levels in Binary Tree
//Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
//Example 1:
//Input:
//    3
//   / \
//  9  20
//    /  \
//   15   7
//Output: [3, 14.5, 11]
//Explanation:
//The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
//Note:
//The range of node's value is in the range of 32-bit signed integer.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//############################### Use of nullptr to track the level ############################### 
vector<double> averageOfLevels(TreeNode* root) { 
  vector<double> ret; 
  double sum = 0, count = 0;
  queue<TreeNode*> q;
  q.push(root);
  q.push(nullptr); //use of nullptr to mark the level of tree
  while (!q.empty()) {
     TreeNode* t = q.front();
     q.pop();
     if (t == nullptr) {
         ret.push_back(sum / count);
         sum = count = 0;
         if (!q.empty()) {
           q.push(nullptr);
         }
     } else {
         sum += t->val;
         ++count;
         if (t->left) q.push(t->left);
         if (t->right) q.push(t->right);
     }
  }
  return ret;
}

//############################### Use of another queue to track the level ############################### 
vector<double> averageOfLevels(TreeNode* root) {
    vector<double> v;
    if(root == nullptr) return v;
    queue<TreeNode*> s1;
    queue<int> s2;
    
    s1.push(root);
    s2.push(0);
    int level = 0;
    while(s1.size()) {
        
        int tmpLev = s2.front();
        
        double avg = 0;
        int count = 0;
        
        while(s2.size() && s2.front() == tmpLev){
            TreeNode* tmp = s1.front(); s1.pop();
            s2.pop();
            if(tmp != nullptr) {
                s1.push(tmp->left);
                s1.push(tmp->right);
                s2.push(tmpLev + 1);
                s2.push(tmpLev + 1);
                ++count;
                avg += tmp->val;
            }
            
        }
        
        if(count != 0)
        v.push_back(avg/count);
    }
    
    return v;
}

//######################################### DFS  ######################################### 
vector<double> averageOfLevels(TreeNode* root) {
        vector<double> alSum;
        vector<int> count;
        traverse(root,0,alSum,count);
        for(int i=0;i<alSum.size();i++) {
          alSum[i] = alSum[i]/count[i];
        }
        return alSum;
    }
        
void traverse(TreeNode* node, int lvl, vector<double>& alSum, vector<int>& cnt) {
     if(node != nullptr) {			
	 if(alSum.size() == lvl) { //At each levels add the node val and update the count
             alSum.push_back((double)node->valSum);
             cnt.push_back(1);
         } else {
             cnt[lvl] =  cnt[lvl]+1;
             alSum[lvl] = alSum[lvl] + node->valSum;
         }                
         traverse(node->left,lvl+1, alSum, cnt); //At each levels 2 path exists (left and right)
	 traverse(node->right,lvl+1, alSum, cnt);
     }
}

//######################################### DFS with pairs ######################################### 
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        map<int, pair<long, int>> info;
        getLevelInfo(root, 0, info);

        vector<double> avgs(info.size());
        for (auto it = info.begin(); it != info.end(); it++) {
            long total = it->second.first;
            int nodes = it->second.second;
            avgs[it->first] = ((double)total) / nodes;
        }
        return avgs;
    }

private:
    void getLevelInfo(TreeNode* node, int l, map<int, pair<long, int>>& info) {
        if (!node) return;
        info[l].first += node->val;
        info[l].second++;
        getLevelInfo(node->left, l + 1, info);
        getLevelInfo(node->right, l + 1, info);
    }
};


//######################################### pytonic ######################################### 
//######################################### stack ######################################### 
//total to represent the sum of each level's node values, and count to represent the number of nodes in each level.
//class Solution(object):
//    def averageOfLevels(self, root):
//        """
//        :type root: TreeNode
//        :rtype: List[float]
//        """
//        stack = [(root, 1)] if root else []
//        total = collections.defaultdict(int)
//        count = collections.defaultdict(int)
//        while stack:
//            node, level = stack.pop()
//            total[level] += node.val
//            count[level] += 1
//            if node.left:
//                stack.append((node.left, level+1))
//            if node.right:
//                stack.append((node.right, level+1))
//        return [1.0 * total[level] / count[level] for level in total]

// vim: set sw=2 sts=2 tw=120 et nospell : 
