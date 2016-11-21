//Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
//For example:
//Given binary tree [3,9,20,null,null,15,7],
//    3
//   / \
//  9  20
//    /  \
//   15   7
//return its zigzag level order traversal as:
//[
//  [3],
//  [20,9],
//  [15,7]
//]
void help(vector<vector<int>>& res,  int level, TreeNode* root) {
	if (res.size() <= level) res.push_back({ root->val });
	else if(level%2) res[level].insert(res[level].begin(),root->val);
	else res[level].push_back(root->val);
	if (root->left) help(res,  level+1, root->left);
	if (root->right) help(res,  level+1, root->right);
}
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	vector<vector<int>> res;
	if (!root) return res;
	help(res, 0, root);
	return res;
}
