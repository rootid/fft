//Binary Tree Vertical Order Traversal
//Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).
//If two nodes are in the same row and column, the order should be from left to right.
//Examples:
//Given binary tree [3,9,20,null,null,15,7],
//    3
//   / \
//  9  20
//    /  \
//   15   7
//return its vertical order traversal as:
//[
//  [9],
//  [3,15],
//  [20],
//  [7]
//]
//Given binary tree [3,9,20,4,5,2,7],
//    _3_
//   /   \
//  9    20
// / \   / \
//4   5 2   7
//return its vertical order traversal as:
//[
//  [4],
//  [9],
//  [3,5,2],
//  [20],
//  [7]
//]

//######################################### BFS traversal  ######################################### 
//Why DFS will not work
//since the nodes in a column are ordered by their row number(depth) 
//we cannot process level x+2 nodes before we process level x.
//If you do DFS, the result has the same List<Integer> elements but in the wrong order

//1. BFS, put node, col into queue at the same time
//2. Every left child access col - 1 while right child col + 1
//3. This maps node into different col buckets
//4. Get col boundary min and max on the fly
//5. Retrieve result from cols
public List<List<Integer>> verticalOrder(TreeNode root) {
    List<List<Integer>> res = new ArrayList<>();
    if (root == null) {
        return res;
    }
    Map<Integer, ArrayList<Integer>> map = new HashMap<>();
    Queue<TreeNode> q = new LinkedList<>();
    Queue<Integer> cols = new LinkedList<>();
    q.add(root); 
    cols.add(0);
    int min = 0;
    int max = 0;
    while (!q.isEmpty()) {
        TreeNode node = q.poll();
        int col = cols.poll();
		map.putIfAbsent(col, new ArrayList<>());
        //if (!map.containsKey(col)) {
        //    map.put(col, new ArrayList<Integer>());
        //}
        map.get(col).add(node.val);
        if (node.left != null) {
            q.add(node.left); 
            cols.add(col - 1);
            min = Math.min(min, col - 1);
        }
        if (node.right != null) {
            q.add(node.right);
            cols.add(col + 1);
            max = Math.max(max, col + 1);
        }
    }
    for (int i = min; i <= max; i++) {
        res.add(map.get(i));
    }
    return res;
}

//######################################### BFS traversal  ######################################### 
//TC : O(n)
//SC : O(n)
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        map<int,vector<int>> hm;  //store sorted nodelist by their height
		//tuple of treenode and vertical distance. (root,0)
        queue<pair<TreeNode*,int>> q;
        q.push({root,0}); 
        while(!q.empty()){
            TreeNode* node = q.front().first;
            int col = q.front().second;
            q.pop();
            hm[col].push_back(node->val);
            if(node->left) {
				q.push({node->left,col-1});
			}
            if(node->right) { 
				q.push({node->right,col+1});
			}
        }
        for(auto i:hm){ 
		  res.push_back(i.second);
        }
    return res;
}

//######################################### BFS queue + dict ######################################### 
def verticalOrder(self, root):
    cols = collections.defaultdict(list)
    queue = [(root, 0)]
    for node, i in queue:
        if node:
            cols[i].append(node.val)
            queue += (node.left, i - 1), (node.right, i + 1)
    return [cols[i] for i in sorted(cols)]

//######################################### BFS queue + dict ######################################### 
def verticalOrder(self, root):
    cols = collections.defaultdict(list)
    queue = collections.deque([(root, 0)])
    while queue:
        node, i = queue.popleft()
        if node:
            cols[i].append(node.val)
            queue += (node.left, i - 1), (node.right, i + 1)
    return [cols[i] for i in sorted(cols)]

//######################################### BFS queue + dict ######################################### 
def verticalOrder(self, root):
    cols = collections.defaultdict(list)
    queue = [(root, 0)]
    i = 0
    while i < len(queue):
        node, x = queue[i]
        i += 1
        if node:
            cols[x].append(node.val)
            queue += (node.left, x - 1), (node.right, x + 1)
    return [cols[x] for x in sorted(cols)]

//######################################### Python dictionary benchmarking ######################################### 
from collections import defaultdict
from timeit import timeit
import random

def livelearn_(a):
    d = defaultdict(list)
    for i in a:
        d[i].append(i)

def livelearn1(a):
    d = defaultdict(list)
    for i in a:
        d[i].append(i)
    ret = [0] * len(d)
    mi = -min(d.keys())
    for k, v in d.items():
        ret[k+mi] = v
    return ret

def livelearn2(a):
    d = defaultdict(list)
    mi = float('inf')
    for i in a:
        mi = min(mi,i)
        d[i].append(i)
    ret = [0] * len(d) 
    for k, v in d.items():
        ret[k-mi] = v
    return ret
    
for e in range(7):
    n = 10**e
    
    a = [0]
    for _ in range(n):
        a.append(a[-1] + random.choice((1, -1)))

    number = 10**7 / n
    t_ = timeit(lambda: livelearn_(a), number=number)
    t1 = timeit(lambda: livelearn1(a), number=number)
    t2 = timeit(lambda: livelearn2(a), number=number)
    print 'n: %7d   livelearn1: %6.3f   livelearn2: %6.3f' % (n, t1 - t_, t2 - t_)




//################################################## No hashmap ################################################## 
private int min = 0, max = 0;
public List<List<Integer>> verticalOrder(TreeNode root) {
    List<List<Integer>> list = new ArrayList<>();
    if(root == null)    return list;
    computeRange(root, 0);
    for(int i = min; i <= max; i++) list.add(new ArrayList<>());
    Queue<TreeNode> q = new LinkedList<>();
    Queue<Integer> idx = new LinkedList<>();
    idx.add(-min);
    q.add(root);
    while(!q.isEmpty()){
        TreeNode node = q.poll();
        int i = idx.poll();
        list.get(i).add(node.val);
        if(node.left != null){
            q.add(node.left);
            idx.add(i - 1);
        }
        if(node.right != null){
            q.add(node.right);
            idx.add(i + 1);
        }
    }
    return list;
}
private void computeRange(TreeNode root, int idx){
    if(root == null)    return;
    min = Math.min(min, idx);
    max = Math.max(max, idx);
    computeRange(root.left, idx - 1);
    computeRange(root.right, idx + 1);
}

//1. Never use LinkedList unless you want instant insertions/removals in the middle. Use ArrayDeque instead.
//2. Better yet, while you're computing the range, compute the number of the nodes in the tree. If the tree is relatively balanced, the number of the nodes on the lowest level should be bounded by (n + 1) / 2—use this value as the initial capacity of the ArrayDeque. If the tree is not balanced, this will introduce more initial allocation overhead than needed.
//3.Since we know the number of elements in list in advance (max - min + 1), we can create it with exact capacity.
//4.Or even better, since the size is fixed anyway, create an array instead and then return Arrays.asList(list).
//5.This is debatable—possibly use one queue instead of two to halve the number of enqueue/dequeue operations. You'll have to create a helper class for that and introduce additional overhead because of that. But then again, here you have boxing/unboxing overhead which is pretty much the same.
//6.With all of these, I get 4 ms. But your solution also yields 4 ms now. Moreover, if I use a separate Range class instead of those two ugly not-really-state-field variables, I get 5 ms, so I guess it's within the margin of error anyway
//
