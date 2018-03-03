//Binary Tree Paths
//Given a binary tree, return all root-to-leaf paths.
//For example, given the following binary tree:
//   1
// /   \
//2     3
// \
//  5
//All root-to-leaf paths are:
//["1->2->5", "1->3"]


//Same as Path-Sum-ii
///the time complexity is usually O(max_length_of_each_path * max_number_of_valid_paths) rather than O(n),
//as each time you find a valid path, you need to copy the array first before
//storing it in the result.
//Even if you use StringBuilder, toString creates a copy of the wrapped char
//array and is not an O(1) operation.
http://grepcode.com/file/repository.grepcode.com/java/root/jdk/openjdk/8u40-b25/java/lang/StringBuilder.java#StringBuilder.toString()
//So the time complexity of your solution is still O(n^2) ---
//max_length_of_each_path = O(n),
//max_number_of_leaves = O(n). This is a very loose bound and the actual time
//complexity may be smaller, but not really O(n)

//NOTE : in Java String are not mutable while StrinBuilder is
//So, during recursion, String always makes copy
//######################################### Recursion + String #########################################
//NOTE : not optimized
//string '+' operations are O(n)
public List<String> binaryTreePaths(TreeNode root) {
    List<String> answer = new ArrayList<String>();
    if (root != null) searchBT(root, "", answer);
    return answer;
}

private void searchBT(TreeNode root, String path, List<String> answer) {
    if (root.left == null && root.right == null) answer.add(path + root.val);
    if (root.left != null) searchBT(root.left, path + root.val + "->", answer);
    if (root.right != null) searchBT(root.right, path + root.val + "->", answer);
}

//######################################### Recursion + StringBuilder #########################################
// T: O(n)
public List<String> binaryTreePaths(TreeNode root) {
    List<String> answer = new ArrayList<String>();
    if (root != null) binaryTreePathHelper(root, new StringBuilder(), answer);
    return answer;
}

private void binaryTreePathHelper(TreeNode root, StringBuilder path, List<String> answer) {
    int initLen = path.length();
    path.append(String.valueOf(root.val));
    if (root.left == null && root.right == null) answer.add(path.toString());
    path.append("->");
    if (root.left != null) binaryTreePathHelper(root.left, path, answer);
    if (root.right != null) binaryTreePathHelper(root.right,path, answer);
    path.setLength(initLen);
}

//######################################### Recursion  #########################################
void binaryTreePaths(vector<string>& result, TreeNode* root, string t) {
    if(!root->left && !root->right) {
        result.push_back(t);
        return;
    }

    if(root->left) binaryTreePaths(result, root->left, t + "->" + to_string(root->left->val));
    if(root->right) binaryTreePaths(result, root->right, t + "->" + to_string(root->right->val));
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> result;
    if(!root) return result;
    binaryTreePaths(result, root, to_string(root->val));
    return result;
}

//######################################### Initializers #########################################
// c++ initializer
// http://en.cppreference.com/w/cpp/utility/initializer_list
vector<string> binaryTreePaths(TreeNode* root) {
  if (root == nullptr)
    return {};
  if (root->left == nullptr && root->right == nullptr)
    return {to_string(root->val)};

  vector<string> left  = binaryTreePaths(root->left);
  vector<string> right = binaryTreePaths(root->right);
  left.insert(left.end(), begin(right), end(right));
  for (auto &e : left)
    e = to_string(root->val) + "->" + e;
  return left;
}


//######################################### python  #########################################
def binaryTreePaths(self, root):
    if not root:
        return []
    return [str(root.val) + '->' + path
            for kid in (root.left, root.right) if kid
            for path in self.binaryTreePaths(kid)] or [str(root.val)]

//######################################### recursion  #########################################
def rootToLeafPaths(self, root):
   if not root: return []
   if not root.left and not root.right: return [str(root.val)]
   return [str(root.val) + '->' + i for i in self.rootToLeafPaths(root.left)] +
             [str(root.val) + '->' + i for i in self.rootToLeafPaths(root.right)]
