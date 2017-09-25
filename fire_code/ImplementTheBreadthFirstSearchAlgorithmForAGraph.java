// Implement a method to find a node in a graph using Breadth First Search.
// Click 'Use me!' to inspect the Node class and its methods.
// Example:
//
//
//          apple
//         /    \                              
//     banana   mango
//    /     \    /     Find
// peach   strawberry
//    \     /
//     cherry
// cherry ==> True

public class ImplementTheBreadthFirstSearchAlgorithmForAGraph {
  public boolean breadthFirstSearch(Node rootNode, String data) {
    if (rootNode == null) return false;
    if (rootNode.data.equals(data)) return true;
    Queue<Node> tq = new LinkedList<>();
    tq.offer(rootNode);
    while (!tq.isEmpty()) {
      Node tmp = tq.poll();
      tmp.visited = true;
      if (tmp.data.equals(data)) return true;
      for (Node node : tmp.adjacentNodes) {
        if (node.visited == false) tq.offer(node);
      }
    }
    return false;
  }
}
