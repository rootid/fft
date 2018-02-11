//Path Sum IV
//If the depth of a tree is smaller than 5, then this tree can be represented by a list of three-digits integers.
//For each integer in this list:
//    The hundreds digit represents the depth D of this node, 1 <= D <= 4.
//    The tens digit represents the position P of this node in the level it belongs to, 1 <= P <= 8. The position is the same as that in a full binary tree.
//    The units digit represents the value V of this node, 0 <= V <= 9.
//Given a list of ascending three-digits integers representing a binary with the depth smaller than 5. You need to return the sum of all paths from the root towards the leaves.
//Example 1:
//Input: [113, 215, 221]
//Output: 12
//Explanation:
//The tree that the list represents is:
//    3
//   / \
//  5   1
//The path sum is (3 + 5) + (3 + 1) = 12.
//Example 2:
//Input: [113, 221]
//Output: 4
//Explanation:
//The tree that the list represents is:
//    3
//     \
//      1
//The path sum is (3 + 1) = 4.
//
//

//Convert to Tree
class Solution {
    int ans = 0;
    public int pathSum(int[] nums) {
        Node root = new Node(nums[0] % 10);
        for (int num: nums) {
            if (num == nums[0]) continue;
            int depth = num / 100, pos = num / 10 % 10, val = num % 10;
            pos--;
            Node cur = root;
            for (int d = depth - 2; d >= 0; --d) {
                if (pos < 1<<d) {
                    if (cur.left == null) cur.left = new Node(val);
                    cur = cur.left;
                } else {
                    if (cur.right == null) cur.right = new Node(val);
                    cur = cur.right;
                }
                pos %= 1<<d;
            }
        }

        dfs(root, 0);
        return ans;
    }

    public void dfs(Node node, int sum) {
        if (node == null) return;
        sum += node.val;
        if (node.left == null && node.right == null) {
            ans += sum;
        } else {
            dfs(node.left, sum);
            dfs(node.right, sum);
        }
    }
}

class Node {
    Node left, right;
    int val;
    Node(int v) {val = v;}
}

//Direct Traversa
class Solution {
    int ans = 0;
    Map<Integer, Integer> values;
    public int pathSum(int[] nums) {
        values = new HashMap();
        for (int num: nums)
            values.put(num / 10, num % 10);

        dfs(nums[0] / 10, 0);
        return ans;
    }

    public void dfs(int node, int sum) {
        if (!values.containsKey(node)) return;
        sum += values.get(node);

        int depth = node / 10, pos = node % 10;
        int left = (depth + 1) * 10 + 2 * pos - 1;
        int right = left + 1;

        if (!values.containsKey(left) && !values.containsKey(right)) {
            ans += sum;
        } else {
            dfs(left, sum);
            dfs(right, sum);
        }
    }
}

//######################################### Iteration  #########################################
//How do we solve problem like this if we were given a normal tree? Yes, traverse it, keep a root to leaf running sum. If we see a leaf node (node.left == null && node.right == null), we add the running sum to the final result.
//Now each tree node is represented by a number. 1st digits is the level, 2nd is the position in that level (note that it starts from 1 instead of 0). 3rd digit is the value. We need to find a way to traverse this tree and get the sum.
//The idea is, we can form a tree using a HashMap. The key is first two digits which marks the position of a node in the tree. The value is value of that node. Thus, we can easily find a node's left and right children using math.
//Formula: For node xy? its left child is (x+1)(y*2-1)? and right child is (x+1)(y*2)?
//Given above HashMap and formula, we can traverse the tree. Problem is solved!
class Solution {
    int sum = 0;
    Map<Integer, Integer> tree = new HashMap<>();

    public int pathSum(int[] nums) {
        if (nums == null || nums.length == 0) return 0;

        for (int num : nums) {
            int key = num / 10;
            int value = num % 10;
            tree.put(key, value);
        }

        traverse(nums[0] / 10, 0);

        return sum;
    }

    private void traverse(int root, int preSum) {
        int level = root / 10;
        int pos = root % 10;
        int left = (level + 1) * 10 + pos * 2 - 1;
        int right = (level + 1) * 10 + pos * 2;

        int curSum = preSum + tree.get(root);

        if (!tree.containsKey(left) && !tree.containsKey(right)) {
            sum += curSum;
            return;
        }

        if (tree.containsKey(left)) traverse(left, curSum);
        if (tree.containsKey(right)) traverse(right, curSum);
    }
}
