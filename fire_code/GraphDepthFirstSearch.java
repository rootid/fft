// Graph Depth First Search
// Implement a method to find a node in a graph using Depth First Search.
// Example:
//          apple
//         /    \                              
//     banana   mango
//    /     \    /
// peach   strawberry
//    \     /
//     cherry
//
// Find cherry ==> true

public class GraphDepthFirstSearch {
  //#Iterative version #
  public boolean depthFirstSearch(Node rootNode, String data) {
    if (rootNode == null) return false;
    Stack<Node> stack = new Stack<>();
    stack.push(rootNode);
    while (!stack.isEmpty()) {
      Node tmp = stack.pop();
      if (tmp.data.equals(data)) return true;
      tmp.visited = true;
      for (Node n : tmp.adjacentNodes) {
        if (n.visited == false) {
          stack.push(n);
        }
      }
    }
    return false;
  }
}
