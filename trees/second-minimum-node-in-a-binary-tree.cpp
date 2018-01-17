//Second Minimum Node In a Binary Tree
//Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.
//Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.
//If no such second minimum value exists, output -1 instead.
//Example 1:
//Input: 
//    2
//   / \
//  2   5
//     / \
//    5   7
//
//Output: 5
//Explanation: The smallest value is 2, the second smallest value is 5.
//Example 2:
//Input: 
//    2
//   / \
//  2   2
//
//Output: -1
//Explanation: The smallest value is 2, but there isn't any second smallest value.

//######################################### BFS traversal ######################################### 
public int findSecondMinimumValue(TreeNode root) {
 
    if(root == null) {
        return -1;
    }
    int min = root.val;
    int secondMin = Integer.MAX_VALUE;
    boolean allsame = true;
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    while(!q.isEmpty()) {
        TreeNode tmp = q.poll();
        if(tmp.left != null) q.offer(tmp.left);
        if(tmp.right != null) q.offer(tmp.right);
         if(tmp.val != min) {
            secondMin = Math.min(secondMin, tmp.val);
            allsame = false;
         }
    }
    if(allsame) return -1;
    return secondMin;
}

//######################################### Priority Queue ######################################### 
//Both TreeSet and Priority queue provides O(log(N)) complexity for adding, removing and searching elements.
public int findSecondMinimumValue(TreeNode root) {
    PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
    add(root,pq);
    if(pq.isEmpty() || pq.size()<3) return -1;
    int temp = pq.poll();
    while(!pq.isEmpty()){
        if(temp!=pq.peek()) return pq.peek();
        pq.poll();
    }
    return -1;
}

public static void add(TreeNode root, PriorityQueue<Integer> pq){
    if(root==null) return;
    pq.add(root.val);
    add(root.left,pq);
    add(root.right,pq);
    return;
}

//######################################### TreeSet ######################################### 
public int findSecondMinimumValue(TreeNode root) {
     TreeSet<Integer> ts = new TreeSet<Integer>();
     add(root, ts);
     ts.pollFirst();
     if(!ts.isEmpty()) return ts.first(); else return -1;
}

//######################################### DFS ######################################### 
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if (!root) return -1;
        int ans = minval(root, root->val);
        return ans;
    }
private:
    int minval(TreeNode* p, int first) {
        if (p == nullptr) return -1;
        if (p->val != first) return p->val;
        int left = minval(p->left, first), right = minval(p->right, first);
        // if all nodes of a subtree = root->val, 
        // there is no second minimum value, return -1
        if (left == -1) return right;
        if (right == -1) return left;
        return min(left, right);
    }
};


//######################################### Naive ######################################### 
class Solution {
public:
    set<int> dict;
    int findSecondMinimumValue(TreeNode* root) {
        preorder(root);
        return dict.size()<=1?-1:*(++dict.begin());
    }
    
    void preorder(TreeNode* root){
        if (!root) return;
        dict.insert(root->val);
        preorder(root->left);
        preorder(root->right);
    }
};

//######################################### Heap ######################################### 
def findSecondMinimumValue(self, root):
    res = []
    queue = [root]
    seen = set()
    for node in queue:
        if node.val not in seen:
            heapq.heappush(res, node.val)
            seen.add(node.val)
        if node.left:
            queue.append(node.left)
            queue.append(node.right)
    heapq.heappop(res)
    return heapq.heappop(res) if res else -1


//######################################### dfs ######################################### 
class Solution(object):
    def findSecondMinimumValue(self, root):
        def dfs(node):
            if node:
                s.add(node.val)
                dfs(node.left)
                dfs(node.right)
        s = set()
        dfs(root)
        s.remove(min(s))
        return min(s) if s else 

//######################################### bfs ######################################### 
class Solution(object):
    def findSecondMinimumValue(self, root):
        q, s = collections.deque([root]), set()
        while q:
            p = q.popleft()
            s.add(p.val)
            if p.left:
                q.append(p.left)
            if p.right:
                q.append(p.right)
        s.remove(min(s))
        return min(s) if s else -1
