//Serialization is the process of converting a data structure or object into a
//sequence of bits so that it can be stored in a file or memory buffer, or
//transmitted across a network connection link to be reconstructed later in the
//same or another computer environment.
//
//Design an algorithm to serialize and deserialize a binary tree. There is no
//restriction on how your serialization/deserialization algorithm should work.
//You just need to ensure that a binary tree can be serialized to a string and
//this string can be deserialized to the original tree structure.
//
//For example, you may serialize the following tree
//
//    1
//   / \
//  2   3
//     / \
//    4   5
//as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a
//binary tree. You do not necessarily need to follow this format, so please be
//creative and come up with different approaches yourself.
//Note: Do not use class member/global/static variables to store states. Your
//serialize and deserialize algorithms should be stateless.
//Use of delimiter ","
//
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
//

//######################################### Preorder traversal + Flow pattern for index scanning  #########################################
public class Codec {

    int idx = -1;
    public String serialize(TreeNode root) {
        String st = "";
        if(root == null) return "#";
        st += String.valueOf(root.val) + "," + serialize(root.left) + "," + serialize(root.right); //recursive preorder traversal
        return st;

    }
    private TreeNode deserializeHelper(String[] data) {
        TreeNode root = null;
        if(idx > data.length) return root;
        idx += 1;
        if(data[idx].equals("#")) return null;
        root = new TreeNode(Integer.parseInt(data[idx]));
        root.left =  deserializeHelper(data);
        root.right = deserializeHelper(data);
        return root;
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        System.out.println(data);
        TreeNode root = null;
        if(data.length() > 0)
            root = deserializeHelper(data.split(","));
        return root;
    }
}

//######################################### Preorder traversal + Flow pattern for index scanning  #########################################
class Codec {
public:
string serialize() {
      if (root == NULL)  {
        return "#";
      }
      return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
}
string serialize_ugly(TreeNode* root) {
      string tmp = "";
      if(root == NULL) {
          tmp += "#";
          return tmp;
      }
      tmp += to_string(root->val);
      tmp += "," + serialize(root->left);
      tmp += "," + serialize(root->right);
      return tmp;
}
TreeNode* deserialize(string data) {
  stringstream ss(data);
  return deserialize_helper(data);
}
TreeNode* deserialize_helper(istringstream& in) {
    string tmp_v;
    geline(in,tmp_v,',');
    if(tmp_v == "#") {
      return NULL;
    }
    TreeNode *root = new TreeNode(stoi(tmp_v));
    root->left = deserialize_helper(in);
    root->right = deserialize_helper(in);
    return root;
}
// Use of delimiiter " "
string serialize(TreeNode* root) {
      if(root == NULL) {
          return "#";
      }
      return  to_string(root->val) + " " + serialize(root->left) + " " + serialize(root->right);
}


TreeNode* deserialize(string data) {
   if (data == "#") return NULL;
   istringstream s(data);
   return deserialize_helper(s);
}

TreeNode* deserialize_helper(istringstream& in) {
    string tmp_v;
    in >> tmp_v;
    if(tmp_v == "#") {
        return NULL;
    }
    TreeNode *root = new TreeNode(stoi(tmp_v));
    root->left = deserialize_helper(in);
    root->right = deserialize_helper(in);
    return root;
}
};

//######################################### Preorder traversal + Flow pattern for index scanning  #########################################
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

//######################################### Preorder traversal + Deque #########################################
public class Codec {

// Encodes a tree to a single string.
public String serialize(TreeNode root) {
    ArrayList<Integer> result = new ArrayList<Integer>();
    serializeHelper(root,result);
    return result.toString();
}

private void serializeHelper(TreeNode root, ArrayList<Integer> result){
    if (root == null) {
        result.add(null);
        return;
    }
    result.add(root.val);
    serializeHelper(root.left,result);
    serializeHelper(root.right,result);
}

// Decodes your encoded data to tree.
public TreeNode deserialize(String data) {
    String[] strArray = data.substring(1,data.length()-1).split(", ");
    Deque<String> strList = new LinkedList<String>(Arrays.asList(strArray));
    return deserializeHelper(strList);
}

private TreeNode deserializeHelper(Deque<String> strList){
    if (strList.size() == 0) return null;
    String str = strList.pop();
    if (str.equals("null")) return null;
    TreeNode currentRoot = new TreeNode(Integer.parseInt(str));
    currentRoot.left = deserializeHelper(strList);
    currentRoot.right = deserializeHelper(strList);
    return currentRoot;
}
}


//######################################### BFS + queue #########################################
public class Codec {
    public String serialize(TreeNode root) {
        if (root == null) return "";
        Queue<TreeNode> q = new LinkedList<>();
        StringBuilder res = new StringBuilder();
        q.add(root);
        while (!q.isEmpty()) {
            TreeNode node = q.poll();
            if (node == null) {
                res.append("n ");
                continue;
            }
            res.append(node.val + " ");
            q.add(node.left);
            q.add(node.right);
        }
        return res.toString();
    }

    public TreeNode deserialize(String data) {
        if (data == "") return null;
        Queue<TreeNode> q = new LinkedList<>();
        String[] values = data.split(" ");
        TreeNode root = new TreeNode(Integer.parseInt(values[0]));
        q.add(root);
        for (int i = 1; i < values.length; i++) {
            TreeNode parent = q.poll();
            if (!values[i].equals("n")) {
                TreeNode left = new TreeNode(Integer.parseInt(values[i]));
                parent.left = left;
                q.add(left);
            }
            if (!values[++i].equals("n")) {
                TreeNode right = new TreeNode(Integer.parseInt(values[i]));
                parent.right = right;
                q.add(right);
            }
        }
        return root;
    }
}

