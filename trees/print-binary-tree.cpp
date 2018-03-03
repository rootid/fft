//Print Binary Tree
//Print a binary tree in an m*n 2D string array following these rules:
//The row number m should be equal to the height of the given binary tree.
//The column number n should always be an odd number.
//The root node's value (in string format) should be put in the exactly middle
//of the first row it can be put. The column and the row where the root node
//belongs will separate the rest space into two parts (left-bottom part and
//right-bottom part). You should print the left subtree in the left-bottom part
//and print the right subtree in the right-bottom part. The left-bottom part
//and the right-bottom part should have the same size. Even if one subtree is
//none while the other is not, you don't need to print anything for the none
//subtree but still need to leave the space as large as that for the other
//subtree. However, if two subtrees are none, then you don't need to leave
//space for both of them.
//Each unused space should contain an empty string "".
//Print the subtrees following the same rules.
//Example 1:
//Input:
//     1
//    /
//   2
//Output:
//[["", "1", ""],
// ["2", "", ""]]
//Example 2:
//Input:
//     1
//    / \
//   2   3
//    \
//     4
//Output:
//[["", "", "", "1", "", "", ""],
// ["", "2", "", "", "", "3", ""],
// ["", "", "4", "", "", "", ""]]
//Example 3:
//Input:
//      1
//     / \
//    2   5
//   /
//  3
// /
//4
//Output:
//[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
// ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
// ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
// ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]
//Note: The height of binary tree is in the range of [1, 10].

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


//################################O Preorder + DFS ################################
class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
		//get the height = m
        int h = height(root);
        int w = 0;
        for (int i = 0; i < h; i++) {
            w = w + 1 + w; //each  w contributes to left anf right subtree
        }
        vector<vector<string>> grid(h, vector<string>(w));
        if (h == 0) return grid;
        print(root, 0, 0, w - 1, grid);
        return grid;
    }

private:
    int height(TreeNode* node) {
        return !node ? 0 : 1 + max(height(node->left), height(node->right));
    }
    //DLR
    void print(TreeNode* node, int d, int l, int r, vector<vector<string>>& grid) {
        if (!node) return;
        int m = (l + r) / 2;
        grid[d][m] = to_string(node->val);
        print(node->left, d + 1, l, m - 1, grid);
        print(node->right, d + 1, m + 1, r, grid);
    }
};

//################################ Preorder + DFS + Start from midIndex ################################
//instead of left and right to calculate the index, Used the mid index and
//derived the left and right indexes from it.
class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
        if (!root) return {};
        if (!root->left && !root->right) return {{to_string(root->val)}};
        int rows = height(root);
        int cols = pow(2, rows)-1;

        vector<vector<string> > res(rows, vector<string>(cols, ""));
        printRecur(root, res, cols/2, cols/2, 0);
        return res;
    }
private :
    void printRecur(TreeNode* root, vector<vector<string> >& res, int idx, int value, int level){
        if (!root) return;
        res[level][idx] = to_string(root->val);
        printRecur(root->left, res, idx-((value+1)/2), value/2, level+1);
        printRecur(root->right, res, idx+(value/2)+1, value/2, level+1);
    }

    int height(TreeNode* root){
        if (!root) return 0;
        return max(height(root->left), height(root->right))+1;
    }
}


//################################ JAVA + Preorder + DFS + Start from midIndex ################################
public List<List<String>> printTree(TreeNode root) {
    List<List<String>> res = new LinkedList<>();
    int height = root == null ? 1 : getHeight(root);
    int rows = height, columns = (int) (Math.pow(2, height) - 1);
    List<String> row = new ArrayList<>();
    for(int i = 0; i < columns; i++)  row.add("");
    for(int i = 0; i < rows; i++)  res.add(new ArrayList<>(row));
    populateRes(root, res, 0, rows, 0, columns - 1);
    return res;
}

public void populateRes(TreeNode root, List<List<String>> res, int row, int totalRows, int i, int j) {
    if (row == totalRows || root == null) return;
    res.get(row).set((i+j)/2, Integer.toString(root.val));
    populateRes(root.left, res, row+1, totalRows, i, (i+j)/2 - 1);
    populateRes(root.right, res, row+1, totalRows, (i+j)/2+1, j);
}

public int getHeight(TreeNode root) {
     if (root == null) return 0;
     return 1 + Math.max(getHeight(root.left), getHeight(root.right));
}

//################################ Preorder + DFS + Start from midIndex ################################
def printTree(self, root):
        if not root: return [""]

        def depth(root):
            if not root: return 0
            return max(depth(root.left), depth(root.right)) + 1

        d = depth(root)
        self.res = [[""] * (2**d - 1) for _ in xrange(d)]

        def helper(node, d, pos):
            self.res[-d - 1][pos] = str(node.val)
            if node.left: helper(node.left, d - 1, pos - 2**(d - 1))
            if node.right: helper(node.right, d - 1, pos + 2**(d - 1))

        helper(root, d - 1, 2**(d - 1) - 1)
        return self.res
