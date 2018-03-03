//Maximum Width of Binary Tree
//Given a binary tree, write a function to get the maximum width of the given
//tree.
//The width of a tree is the maximum width among all levels. The binary tree
//has the same structure as a full binary tree, but some nodes are null.
//The width of one level is defined as the length between the end-nodes (the
//leftmost and right most non-null nodes in the level, where the null nodes
//between the end-nodes are also counted into the length calculation.
//Example 1:
//Input:
//           1
//         /   \
//        3     2
//       / \     \
//      5   3     9
//Output: 4
//Explanation: The maximum width existing in the third level with the length 4
//(5,3,null,9).
//Example 2:
//Input:
//          1
//         /
//        3
//       / \
//      5   3
//Output: 2
//Explanation: The maximum width existing in the third level with the length 2
//(5,3).
//Example 3:
//Input:
//          1
//         / \
//        3   2
//       /
//      5
//Output: 2
//Explanation: The maximum width existing in the second level with the length 2
//(3,2).
//Example 4:
//Input:
//          1
//         / \
//        3   2
//       /     \
//      5       9
//     /         \
//    6           7
//Output: 8
//Explanation:The maximum width existing in the fourth level with the length 8
//(6,null,null,null,null,null,null,7).
//Note: Answer will in the range of 32-bit signed integer.

//Left-most and right-most nodes must be non-null
//level ?

//######################################### Heap like solution + Preorder #########################################
//We know that a binary tree can be represented by an array (assume the root
//begins from the position with index 1 in the array).
//If the index of a node is i, the indices of its two children are 2*i and 2*i
//+ 1.
//The idea is to use two arrays (start[] and end[]) to record the the indices
//of the leftmost node and rightmost node in each level, respectively.
// For each level of the tree, the width is end[level] - start[level] + 1. Then, we just need to find the maximum widt
public int widthOfBinaryTree(TreeNode root) {
    return dfs(root, 0, 1, new ArrayList<Integer>(), new ArrayList<Integer>());
}

public int dfs(TreeNode root, int level, int childIdx, List<Integer> start, List<Integer> end) {
    if(root == null)return 0;
    if(start.size() == level) { // Traversal arrives a new level of the tree, we need to extend the size of array start and end to put the start index and the end index of this new level into them
        start.add(childIdx);
		end.add(childIdx);
    } else {
		end.set(level, childIdx); //Traversal is in a visited level, then we just need to update the end index of this level.
	}
    int cur = end.get(level) - start.get(level) + 1;
    int left = dfs(root.left, level + 1, 2*childIdx, start, end);
    int right = dfs(root.right, level + 1, 2*childIdx + 1, start, end);
    return Math.max(cur, Math.max(left, right));
}


//######################################### Heap like solution #########################################
int widthOfBinaryTree(TreeNode* root) {
    return dfs(root, 0, 1, vector<pair<int, int>>() = {});
}

int dfs(TreeNode* root, int level, int childIdx, vector<pair<int, int>>& vec){
    if(root == NULL)return 0;
    if(vec.size() == level)vec.push_back({childIdx, childIdx});
    else vec[level].second = childIdx;
    return max({vec[level].second - vec[level].first + 1, dfs(root->left, level + 1, 2*childIdx, vec), dfs(root->right, level + 1, 2*childIdx + 1, vec)});
}


//######################################### DFS#########################################
private int max = 1;
public int widthOfBinaryTree(TreeNode root) {
    if (root == null) return 0;
    List<Integer> startOfLevel = new LinkedList<>();
    helper(root, 0, 1, startOfLevel);
    return max;
}
public void helper(TreeNode root, int level, int index, List<Integer> list) {
    if (root == null) return;
    if (level == list.size()) list.add(index);
    max = Math.max(max, index + 1 - list.get(level));
    helper(root.left, level + 1, index * 2, list);
    helper(root.right, level + 1, index * 2 + 1, list);
}


//######################################### Heap indexing DFS #########################################
//The main idea with this question is we will give each node a position value.
//If we go down the left neighbor, then position -> position * 2; and if we go
//down the right neighbor, then position -> position * 2 + 1. This makes it so
//that when we look at the position values L and R of two nodes with the same
//depth, the width will be R - L + 1.
//From there, we have two choices for traversals: BFS or DFS. In a BFS, all the
//nodes with the same depth are searched adjacent to each other, so we only
//need to remember the first and last positions seen for each depth.

def widthOfBinaryTree(self, root):
    queue = [(root, 0, 0)]
    cur_depth = left = ans = 0
    for node, depth, pos in queue:
        if node:
            queue.append((node.left, depth+1, pos*2))
            queue.append((node.right, depth+1, pos*2 + 1))
            if cur_depth != depth:
                cur_depth = depth
                left = pos
            ans = max(pos - left + 1, ans)
    return ans

//######################################### Heap indexing BFS #########################################
//It might be more natural to attempt a DFS. Here, we create a dfs iterator
//that yields the depth and position of each node.
//After, we need to know for each depth, what was the leftmost position
//left[depth] and the rightmost position right[depth].
//We'll remember the largest width as we iterate through the nodes.

def widthOfBinaryTree(self, root):
    def dfs(node, depth = 0, pos = 0):
        if node:
            yield depth, pos
            yield from dfs(node.left, depth + 1, pos * 2)
            yield from dfs(node.right, depth + 1, pos * 2 + 1)

    left = {}
    right = {}
    ans = 0
    for depth, pos in dfs(root):
        left[depth] = min(left.get(depth, pos), pos)
        right[depth] = max(right.get(depth, pos), pos)
        ans = max(ans, right[depth] - left[depth] + 1)

    return ans

//######################################### Heap indexing #########################################
//        1
//   2         3
// 4   5     6   7
//8 9 x 11  x 13 x 15
//Regardless whether these nodes exist:
//Always make the id of left child as parent_id * 2;
//Always make the id of right child as parent_id * 2 + 1;
//So we can just:
//Record the id of left most node when first time at each level of the tree
//during an pre-order run.(you can tell by check the size of the container to
//hold the first nodes);
//At each node, compare the distance from it the left most node with the
//current max width;
//DFS - Return Value

//######################################### Heap indexing DFS #########################################
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        vector<int> lefts; // left most nodes at each level;
        return dfs(root, 1, 0, lefts);
    }
private:
    int dfs(TreeNode* n, int id, int d, vector<int>& lefts) { // d : depth
        if (!n) return 0;
        if (d >= lefts.size()) lefts.push_back(id);  // add left most node
        return max({id + 1 - lefts[d], dfs(n->left, id * 2, d + 1, lefts), dfs(n->right, id * 2 + 1, d + 1, lefts)});
    }
};
3 liner

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        unordered_map<int, vector<int>> m;
        function<int(TreeNode*, int, int)> dfs = [&](TreeNode* n, int id, int d){ return n ? m[d].push_back(id), max({id+1-m[d][0], dfs(n->left, id*2, d+1), dfs(n->right, id*2+1, d+1)}) : 0; };
        return dfs(root, 1, 0);
    }
};
//######################################### Heap indexing DFS #########################################
class Solution {
    public int widthOfBinaryTree(TreeNode root) {
        List<Integer> lefts = new ArrayList<Integer>(); // left most nodes at each level;
        return dfs(root, 1, 0, lefts);
    }

    private int dfs(TreeNode n, int id, int d, List<Integer> lefts) { // d : depth
        if (n == null) return 0;
        if (d >= lefts.size()) lefts.add(id);   // add left most node
        return Math.max(id + 1 - lefts.get(d), Math.max(dfs(n.left, id*2, d+1, lefts), dfs(n.right, id*2+1, d+1, lefts)));
    }
}
//######################################### Heap indexing DFS + Side effects #########################################
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        vector<int> lefts; // left most nodes at each level;
        int maxwidth = 0;
        dfs(root, 1, 0, lefts, maxwidth);
        return maxwidth;
    }
private:
    void dfs(TreeNode* node, int id, int depth, vector<int>& lefts, int& maxwidth) {
        if (!node) return;
        if (depth >= lefts.size()) lefts.push_back(id);  // add left most node
        maxwidth = max(maxwidth, id + 1 - lefts[depth]);
        dfs(node->left, id * 2, depth + 1, lefts, maxwidth);
        dfs(node->right, id * 2 + 1, depth + 1, lefts, maxwidth);
    }
};
//######################################### Heap indexing DFS + Side effects #########################################
class Solution {
    public int widthOfBinaryTree(TreeNode root) {
        List<Integer> lefts = new ArrayList<Integer>(); // left most nodes at each level;
        int[] res = new int[1]; // max width
        dfs(root, 1, 0, lefts, res);
        return res[0];
    }
    private void dfs(TreeNode node, int id, int depth, List<Integer> lefts, int[] res) {
        if (node == null) return;
        if (depth >= lefts.size()) lefts.add(id);   // add left most node
        res[0] = Integer.max(res[0], id + 1 - lefts.get(depth));
        dfs(node.left,  id * 2,     depth + 1, lefts, res);
        dfs(node.right, id * 2 + 1, depth + 1, lefts, res);
    }
}
//######################################### Heap indexing BFS #########################################
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int max = 0;
        queue<pair<TreeNode*, int>> q;
        q.push(pair<TreeNode*, int>(root, 1));
        while (!q.empty()) {
            int l = q.front().second, r = l; // right started same as left
            for (int i = 0, n = q.size(); i < n; i++) {
                TreeNode* node = q.front().first;
                r = q.front().second;
                q.pop();
                if (node->left) q.push(pair<TreeNode*, int>(node->left, r * 2));
                if (node->right) q.push(pair<TreeNode*, int>(node->right, r * 2 + 1));
            }
            max = std::max(max, r + 1 - l);
        }
        return max;
    }
};
//######################################### Heap indexing BFS #########################################
import java.util.AbstractMap;
class Solution {
    public int widthOfBinaryTree(TreeNode root) {
        if (root == null) return 0;
        int max = 0;
        Queue<Map.Entry<TreeNode, Integer>> q = new LinkedList<Map.Entry<TreeNode, Integer>>();
        q.offer(new AbstractMap.SimpleEntry(root, 1));

        while (!q.isEmpty()) {
            int l = q.peek().getValue(), r = l; // right started same as left
            for (int i = 0, n = q.size(); i < n; i++) {
                TreeNode node = q.peek().getKey();
                r = q.poll().getValue();
                if (node.left != null) q.offer(new AbstractMap.SimpleEntry(node.left, r * 2));
                if (node.right != null) q.offer(new AbstractMap.SimpleEntry(node.right, r * 2 + 1));
            }
            max = Math.max(max, r + 1 - l);
        }

        return maxwidth;
    }
}

