//Binary Tree Level Order Traversal
//Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

//For example:
//Given binary tree {3,9,20,#,#,15,7}
//
//    3
//   / \
//  9  20
//    /  \
//   15   7
//[
//  [3],
//  [9,20],
//  [15,7]
//]
//

//######################################### BFS  ######################################### 
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode *> nodes;
        if (!root) {
            return res;
        }
        nodes.push(root);
        while (!nodes.empty()) {
            int level = nodes.size();
            vector<int> tmp;
            for (int i = 0; i < level; ++i) {
                if (nodes.front()->left) {
                    nodes.push(nodes.front()->left);
                }
                if (nodes.front()->right) {
                    nodes.push(nodes.front()->right);
                }
                tmp.push_back(nodes.front()->val);
                nodes.pop();
            }
            
            res.push_back(tmp);
        }
        return res;
    }
};

//######################################### DFS ######################################### 
//SC : O(log n) 
vector<vector<int>> ret;

void buildVector(TreeNode *root, int depth)
{
    if(root == NULL) return;
    if(ret.size() == depth)
        ret.push_back(vector<int>());
    
    ret[depth].push_back(root->val);
    buildVector(root->left, depth + 1);
    buildVector(root->right, depth + 1);
}

//######################################### DFS : Only ref ######################################### 
vector<vector<int> > levelOrder(TreeNode *root) {
    buildVector(root, 0);
    return ret;
}

   void buildVector(TreeNode *root, int depth,vector<vector<int>> & ret)
    {
        if(root == NULL) return;
        if(ret.size() == depth)
            ret.push_back(vector<int>());
        
        ret[depth].push_back(root->val);
        buildVector(root->left, depth + 1, ret);
        buildVector(root->right, depth + 1, ret);
    }
    
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int>> ret;
        buildVector(root, 0, ret);
        return ret;
    }

//######################################### DFS ######################################### 
public class Solution {
    List<List<Integer>> returnList = new ArrayList<List<Integer>>();
    public List<List<Integer>> levelOrder(TreeNode root) {
        func(root,0);
        return returnList;

    }
    public void func(TreeNode root,int level) {
        if(root==null) {
            return;
        }
        //VISIT
        if(returnList.size() >= level+1) {
            List<Integer> l = returnList.get(level);
            l.add(root.val);
        }
        else {
            List<Integer> temp  = new ArrayList<Integer>();
            temp.add(root.val);
            returnList.add(level,temp);
        }
        //go left and right
        func(root.left,level+1);
        func(root.right,level+1);
    }
}

//######################################### python ######################################### 
# solution 1
def levelOrderBottom(self, root):
    if not root:
        return []
    level = [root]
    stack = []
    while level:
        stack.append([each.val for each in level])
        level = [node for each in level for node in (each.left, each.right) if node]
    return stack[::-1]

# solution 2
def levelOrderBottom(self, root):
    if not root:
        return []
    levels = [[root]]
    result = []
    while levels:
        curlevel = levels.pop()
        newlevel, curvalues = [], []
        for each in curlevel:
            if each:
                curvalues += [each.val]
                newlevel += [each.left, each.right]
        if curvalues:
            result.append(curvalues)
        if newlevel:
            levels.append(newlevel)
    return result[::-1]


def levelOrderBottom(self, root):
    out, level = [], [root]
    if root:
        while level:
            out += [],
            add = out[-1].append
            level = [kid
                     for node in level if not add(node.val)
                     for kid in (node.left, node.right) if kid]
    return out[::-1]


>>> from timeit import timeit
>>> def test_append():
        x = []
        for i in xrange(100):
            x += [i]

>>> def test_list_comprehension():
        x = [i for i in xrange(100)]
        
>>> timeit(test_append, number=100000)
4.446563311239515
>>> timeit(test_list_comprehension, number=100000)
1.0300341831108426
>>> 

//######################################### Bottom up traversal  ######################################### 
void DFSHelper(TreeNode* root,vector< vector<int> >& result, int level) {
  
  if(!root) {
    return;
  }
  //create a new vector for each current level
	if (result.empty() || level > (result.size() - 1)) {
		result.push_back(vector<int>());
	}
  result[level].push_back(root->val);
  DFSHelper(root->left,result,level+1);
  DFSHelper(root->right,result,level+1);
}

vector<vector<int> > levelOrderBottom(TreeNode* root) {

  vector< vector<int> > result;
  int level = 0;
  DFSHelper(root,result,level);
  reverse(result.begin(),result.end());
  return result;

}

vector<vector<int> > levelOrderBottom(TreeNode* root) {

  vector< vector<int> > result;
  
  if(!root) {
    return result;
  }
  queue<TreeNode* > qStore;
  qStore.push(root);

  while(!qStore.empty()) {
    int level = qStore.size();
    vector<int> visited;
    while(level-- > 0){
        TreeNode *tmp = qStore.front();
        visited.push_back(tmp->val);
        qStore.pop();
        if(tmp->left) {
          qStore.push(tmp->left);
        }
        if(tmp->right) {
          qStore.push(tmp->right);
        }
    }
    result.push_back(visited);
    visited.clear();
  }
  reverse(result.begin(),result.end());
  return result;

}

