//Binary Tree Zigzag Level Order Traversal
//Given a binary tree, return the zigzag level order traversal of its nodes'
//values. (ie, from left to right, then right to left for the next level and
//alternate between).
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

//######################################### Recursion #########################################
//T : O(N)
public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
    List<List<Integer>> res = new ArrayList<List<Integer>>();
    addList(res, root, 0);
    return res;
}

public void addList(List<List<Integer>> res, TreeNode root, int level){
    if(root == null) return;
    if (level >= res.size()){
        res.add(new LinkedList<Integer>());
    }
    if (level%2 == 1) res.get(level).add(root.val);
    else res.get(level).add(0, root.val);
    addList(res, root.right, level + 1);
    addList(res, root.left, level + 1);

}

//######################################### Iterative  #########################################
public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        if (root == null) return res;
        Queue<TreeNode> queue = new LinkedList<>();
        queue.add(root);
        boolean zigzag = false;
        while (!queue.isEmpty()) {
            LinkedList<Integer> level = new LinkedList<>();
            int cnt = queue.size();
            for (int i = 0; i < cnt; i++) {
                TreeNode node = queue.poll();
                if (zigzag) {
                    level.addFirst(node.val);
                }
                else {
                    level.addLast(node.val);
                }
                if (node.left != null) {
                    queue.add(node.left);
                }
                if (node.right != null) {
                    queue.add(node.right);
                }
            }
            res.add(level);
            zigzag = !zigzag;
        }
        return res;
    }

//######################################### Recursion #########################################
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
