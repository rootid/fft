//Verify Preorder Serialization of a Binary Tree
//One way to serialize a binary tree is to use pre-order traversal. When we
//encounter a non-null node, we record the node's value. If it is a null node,
//we record using a sentinel value such as #.
//     _9_
//    /   \
//   3     2
//  / \   / \
// 4   1  #  6
/// \ / \   / \
//# # # #   # #
//For example, the above binary tree can be serialized to the string
//"9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.
//Given a string of comma separated values, verify whether it is a correct
//preorder traversal serialization of a binary tree. Find an algorithm without
//reconstructing the tree.
//Each comma separated value in the string must be either an integer or a
//character '#' representing null pointer.
//You may assume that the input format is always valid, for example it could
//never contain two consecutive commas such as "1,,3".
//Example 1:
//"9,3,4,#,#,1,#,#,2,#,6,#,#"
//Return true
//Example 2:
//"1,#"
//Return false
//Example 3:
//"9,#,#,1"
//Return false


//######################################### Link counting (non-leaf [+2(out),-1(in)],leaf[0,-1]) #########################################
public boolean isValidSerialization(String preorder) {
    String[] nodes = preorder.split(",");
    int diff = 1;
    for (String node: nodes) {
        if (--diff < 0) return false; // Visit node =>  -1 counter; or (1 incoming link) link counting
        if (!node.equals("#")) diff += 2; //if non empty node +2 for next  (2 links)
    }
    return diff == 0;
}

//Suppose we try to build this tree. During building, we record the difference
//between out degree and in degree
//diff = outdegree - indegree.
//When the next node comes, we then decrease diff by 1, because the node
//provides an in degree.
//If the node is not null, we increase diff by 2, because it provides two out
//degrees.
//If a serialization is correct, diff should never be negative and diff will be
//zero when finishe

//######################################### Reduction with single traversal #########################################
bool isValidSerialization(string preorder_str) {
  const char* preorder = preorder_str.c_str();
  int nulls, nodes;
  char pre;
  //pre : next character
  for (nulls = nodes = 0; *preorder; pre = *preorder++) {
      if (*preorder == ',') {
          pre == '#' ? nulls++ : nodes++;
          if (nodes < nulls) {
              return false;
          }
      }
  }
  return pre == '#' && nulls == nodes;
}


//######################################### Reduction with single traversal #########################################
bool isValidSerialization(string preorder) {
  //stringstream ss.str(preorder);
  stringstream ss;
  ss << preorder;
  string t;
  vector<string> v;
  while (getline(ss, t, ',')) {
    v.push_back(t);
  }
  int t_len = v.size();
  int nodes=0, nulls=0;
  for(int i = 0; i<t_len; i++){
      if(v[i]=="#") {
        ++nulls;
      } else {
        ++nodes;
      }
      if(nulls >= nodes+1 && i != t_len-1 ) return false;
  }
  return nulls == nodes+1;
}

//######################################### Reduction with single traversal with stack #########################################
//Reduction n,#,# => #
public boolean isValidSerialization(String preorder) {
  if (preorder == null) return false;

  Stack<String> st = new Stack<>();
  String[] strs = preorder.split(",");
  for (String curr : strs) {
    if (curr.equals("#")) {
      // replace a number node and its left child "#" to a "#" node.
      while (!st.isEmpty() && st.peek().equals("#")) {
        st.pop();
        if (st.isEmpty()) return false;
        st.pop();
      }
    }
    st.push(curr);
  }
  return st.size() == 1 && st.peek().equals("#");
}

