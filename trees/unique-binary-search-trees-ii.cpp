//Unique Binary Search Trees II
//Given an integer n, generate all structurally unique BST's (binary search
//trees) that store values 1...n.
//For example,
//Given n = 3, your program should return all 5 unique BST's shown below.
//   1         3     3      2      1
//    \       /     /      / \      \
//     3     2     1      1   3      2
//    /     /       \                 \
//   2     1         2                 3

vector<TreeNode*> generateTrees(int n) {
    if(n==0)  return vector<TreeNode*>{};
    return helper(1, n);
}

vector<TreeNode*> helper(int s, int e){
    vector<TreeNode*> result;
    if(s>e)  return {NULL}; // NOTE : don't return NULL use {NULL}
    for(int i=s; i<=e; i++){
        vector<TreeNode*> left=helper(s, i-1);
        vector<TreeNode*> right=helper(i+1, e);
        for(auto l:left){
            for(auto r:right){
                TreeNode* root=new TreeNode(i);
                root->left=l;
                root->right=r;
                result.push_back(root);
            }
        }
    }
    return result;
}

//############################# pytonic list comprehenssion #############################
//def generateTrees(self, n):
//    def node(val, left, right):
//        node = TreeNode(val)
//        node.left = left
//        node.right = right
//        return node
//    def trees(first, last):
//        return [node(root, left, right)
//                for root in range(first, last+1)  #(s,e)
//                for left in trees(first, root-1) #left (s,r-1)
//                for right in trees(root+1, last)] or [None] #left (r+1,e)
//    return trees(1, n)
//
//def node(val, left, right):
//    node = TreeNode(val)
//    node.left = left
//    node.right = right
//    return node
//
//class Solution:
//    def generateTrees(self, last, first=1):
//        return [node(root, left, right)
//                for root in range(first, last+1)
//                for left in self.generateTrees(root-1, first)
//                for right in self.generateTrees(last, root+1)] or [None]
//
//############################# pytonic loops #############################
//def generateTrees(self, n):
//    def generate(first, last):
//        trees = []
//        for root in range(first, last+1):
//            for left in generate(first, root-1):
//                for right in generate(root+1, last):
//                    node = TreeNode(root)
//                    node.left = left
//                    node.right = right
//                    trees += node,
//        return trees or [None]
//    return generate(1, n)
//
