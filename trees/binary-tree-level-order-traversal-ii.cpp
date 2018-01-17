//Binary Tree Level Order Traversal II
//Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).
//For example:
//Given binary tree [3,9,20,null,null,15,7],
//    3
//   / \
//  9  20
//    /  \
//   15   7
//return its bottom-up level order traversal as:
//[
//  [15,7],
//  [9,20],
//  [3]
//]

//############################### BFS  ###############################
  public List<List<Integer>> levelOrderBottom(TreeNode root) {     
        List<List<Integer>> result = new ArrayList<>();
        if(root == null) return result;
        Queue<TreeNode> q = new ArrayDeque<>();
        q.offer(root);
        while(!q.isEmpty()) {
                int level = q.size();
                LinkedList<Integer> visitedList = new LinkedList<>();
                for(int i=0;i<level;i++) {
                    TreeNode tmp = q.poll();
                    if(tmp.left != null)  q.offer(tmp.left);
                    if(tmp.right != null)  q.offer(tmp.right);
                    visitedList.add(tmp.val);
                }
                result.add(0, visitedList);
        }
        return result;
    }

//############################### DFS ###############################
    public List<List<Integer>> levelOrderBottom(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        levelOrderBottomHelper(root,result,0);
        return result;
    }
    
    private void levelOrderBottomHelper(TreeNode root, List<List<Integer>> result, int level) {
        if(root != null) {
            if(result.size() == level) result.add(0, new ArrayList<>()); // inject list at 0th position
            levelOrderBottomHelper(root.left, result,level + 1);
            levelOrderBottomHelper(root.right, result,level + 1);
            result.get(result.size() - 1 - level).add(root.val); // add the element in reverse order
        }
    }

//############################### Optimizied O(N)###############################
def levelOrderBottom(self, root):
        res, queue = [], [root]
        while queue:
            res.append([node.val for node in queue if node])
            queue = [child for node in queue if node for child in (node.left, node.right)]
        return res[-2::-1]

//############################### Optimizied O(N) with deque ###############################
def levelOrderBottom(self, root):
    queue, res = collections.deque([(root, 0)]), []
    while queue:
        node, level = queue.popleft()
        if node:
            if level == len(res):
                res.append([])
            res[level].append(node.val)
            queue.append((node.left, level + 1))
            queue.append((node.right, level + 1))
    return res[::-1]


//NOTE : insert has complexity O(N) makes below solutions O(N^2)
//###############################dfs + Recursion ###############################
def levelOrderBottom1(self, root):
    res = []
    self.dfs(root, 0, res)
    return res

def dfs(self, root, level, res):
    if root:
        if len(res) < level + 1:
            res.insert(0, [])
        res[-(level+1)].append(root.val)
        self.dfs(root.left, level+1, res)
        self.dfs(root.right, level+1, res)
        
//###############################dfs+ stack###############################
def levelOrderBottom2(self, root):
    stack = [(root, 0)]
    res = []
    while stack:
        node, level = stack.pop()
        if node:
            if len(res) < level+1:
                res.insert(0, [])
            res[-(level+1)].append(node.val)
            stack.append((node.right, level+1))
            stack.append((node.left, level+1))
    return res
 
//###############################bfs + queue###############################
def levelOrderBottom(self, root):
    queue, res = collections.deque([(root, 0)]), []
    while queue:
        node, level = queue.popleft()
        if node:
            if len(res) < level+1:
                res.insert(0, [])
            res[-(level+1)].append(node.val)
            queue.append((node.left, level+1))
            queue.append((node.right, level+1))
    return res
