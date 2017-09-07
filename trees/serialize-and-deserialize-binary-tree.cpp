Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

//######################################### Preorder TRaversal  ######################################### 
//######################################### Serialize ######################################### 
public String serializeTree(TreeNode root){
    StringBuilder sb = new StringBuilder();
    serializeTree(root, sb);
    return sb.toString();
}

public void serializeTree(TreeNode root, StringBuilder sb){
    if(root == null) sb.append("null,");
    else {
        sb.append(root.data).append(",");
        serializeTree(root.left, sb);
        serializeTree(root.right, sb); 
	}
}
//######################################### Deserialize ######################################### 
public TreeNode restoreTree(String str){
    if(str == null) return null;
    return restoreTree(new LinkedList(Arrays.asList(str.split(","))));
}

public TreeNode restoreTree(LinkedList<String> arr){
    String data = arr.remove(0);
    if(data.equals("null")) return null;
    
    TreeNode curr = new TreeNode(Integer.parseInt(data));
    curr.left = restoreTree(arr);
    curr.right = restoreTree(arr);
    return curr;
}


//######################################### Python ######################################### 
class Codec:

    def serialize(self, root):
        code, queue = "", [root]
        for node in queue:
            code += "," * (node != root) + "#" * (not node) + (str(node.val) if node else "")
            if node: queue += node.left, node.right,
        return code
        
    def deserialize(self, data):
        data = collections.deque(data.split(","))
        val = data.popleft()
        root = TreeNode(int(val)) if val != "#" else None
        queue = [root]
        for node in queue:
            if not node: continue
            l, r = data.popleft(), data.popleft()
            node.left  = TreeNode(int(l)) if l != "#"  else None
            node.right = TreeNode(int(r)) if r != "#" else None
            queue += node.left, node.right,
        return root

		
//######################################### Python ######################################### 
class Codec:

    def serialize(self, root):
        def doit(node):
            if node:
                vals.append(str(node.val))
                doit(node.left)
                doit(node.right)
            else:
                vals.append('#')
        vals = []
        doit(root)
        return ' '.join(vals)

    def deserialize(self, data):
        def doit():
            val = next(vals)
            if val == '#':
                return None
            node = TreeNode(int(val))
            node.left = doit()
            node.right = doit()
            return node
        vals = iter(data.split())
        return doit()

//######################################### Recursive ######################################### 
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Codec {

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        StringBuilder sb=new StringBuilder();
        dfs(root,sb);
        return sb.toString();
    }
    private void dfs(TreeNode x, StringBuilder sb) {
        if (x==null) {
            sb.append("null ");
            return;
        }
        sb.append(String.valueOf(x.val));
        sb.append(' ');
        dfs(x.left,sb);
        dfs(x.right,sb);
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        String[] node=data.split(" ");
        int[] d=new int[1];
        return dfs(node,d);
    }
    private TreeNode dfs(String[] node, int[] d) {
        if (node[d[0]].equals("null")) {
            d[0]++;
            return null;
        }
        TreeNode x=new TreeNode(Integer.valueOf(node[d[0]]));
        d[0]++;
        x.left=dfs(node,d);
        x.right=dfs(node,d);
        return x;
    }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.deserialize(codec.serialize(root));
