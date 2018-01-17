//Find Duplicate Subtrees
//Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the root node of any one of them.
//Two trees are duplicate if they have the same structure with same node values.
//Example 1: 
//        1
//       / \
//      2   3
//     /   / \
//    4   2   4
//       /
//      4
//The following are two duplicate subtrees:
//      2
//     /
//    4
//and
//    4
//Therefore, you need to return above trees' root in the form of a list.
//

//######################################## DLR serialization ######################################## 
string preorder(TreeNode* root, unordered_map<string, int>& freq, vector<TreeNode*>& res) {
      if(root != NULL) {
          string left = preorder(root -> left, freq, res);
          string right = preorder(root -> right, freq, res);
          
          string str = to_string(root -> val) + " " + left + right;
          
          if(freq[str] == 1) res.push_back(root);
          freq[str]++;
          return str;
      } else {
          return "null ";
      }
  }
  vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
      unordered_map<string, int> freq;
      vector<TreeNode*> res;
      preorder(root, freq, res);
      return res;
  }

//######################################## LDR serialization ######################################## 
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, vector<TreeNode*> > map;
        vector<TreeNode*> dups;
        serialize(root, map);
        for (auto it = map.begin(); it != map.end(); it++) {
            if (it->second.size() > 1) {
                dups.push_back(it->second[0]);
            }
        }
        return dups;
    }

private:
    string serialize(TreeNode* node, unordered_map<string, vector<TreeNode*>>& map) {
        if (!node) return "";
        string s = "(" + serialize(node->left, map) + to_string(node->val) + serialize(node->right, map) + ")";
        map[s].push_back(node);
        return s;
    }

//######################################### Pytonic ######################################### 
//######################################### Simple Serialization ######################################### 
def findDuplicateSubtrees(self, root):
        def trv(root):
            if not root: return "null"
            struct = "%s,%s,%s" % (str(root.val), trv(root.left), trv(root.right))
            nodes[struct].append(root)
            return struct
        
        nodes = collections.defaultdict(list)
        ret = []
        trv(root)
        return [nodes[struct][0] for struct in nodes if len(nodes[struct]) > 1]
//######################################### Serialization with tuples ######################################### 
//I convert the entire tree of nested TreeNodes to a tree of nested tuples. 
//Those have the advantage that they already support hashing and deep comparison (for the very unlikely cases of hash collisions). 
//So then I can just use each subtree's tuple version as a key in my dictionary. 
//And equal subtrees have the same key and thus get collected in the same list.
//Overall this costs only O(n) memory (where n is the number of nodes in the given tree). 
//The string serialization I've seen in other posted solutions costs O(n^2) memory (and thus also at least that much time).

def findDuplicateSubtrees(self, root):
    def tuplify(root):
        if root:
            tuple = root.val, tuplify(root.left), tuplify(root.right)
            trees[tuple].append(root)
            return tuple
    trees = collections.defaultdict(list)
    tuplify(root)
    return [roots[0] for roots in trees.values() if roots[1:]]


//######################################### Serialization with Merkel hash ######################################### 
//Assign every subtree a unique merkle hash.
// https://discuss.leetcode.com/topic/88520/python-straightforward-with-explanation-o-st-and-o-s-t-approaches
def findDuplicateSubtrees(self, root):
    from hashlib import sha256
    def hash_(x):
        S = sha256()
        S.update(x)
        return S.hexdigest()

    def merkle(node):
        if not node:
            return '#'
        m_left = merkle(node.left)
        m_right = merkle(node.right)
        node.merkle = hash_(m_left + str(node.val) + m_right)
        count[node.merkle].append(node)
        return node.merkle

    count = collections.defaultdict(list)
    merkle(root)
    return [nodes.pop() for nodes in count.values() if len(nodes) >= 2]
