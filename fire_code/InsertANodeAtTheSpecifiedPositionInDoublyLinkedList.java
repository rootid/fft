import java.util.*;
// In doubly linked list, implement a method to insert a node at specified
// position and return the list's head. Do nothing if insertion position is
// outside the bounds of the list.
// Examples:
// insertAtPos(1<=>2<=>3,4,2) ==> 1<=>4<=>2<=>3
// insertAtPos(1,4,3) ==> 1
public class InsertANodeAtTheSpecifiedPositionInDoublyLinkedList {
  public DoublyLinkedNode insertAtPos(DoublyLinkedNode head, int data,
                                      int pos) {
    DoublyLinkedNode newNode = new DoublyLinkedNode(data);
    // insert at first location in empty list
    if (head == null && pos == 1) return newNode;
    // empty node + pos > 1
    if (head == null) return head;
    DoublyLinkedNode pre = new DoublyLinkedNode(0);
    DoublyLinkedNode last = null;
    DoublyLinkedNode current = head;
    current.prev = pre;
    pre.next = current;
    current = pre;
    while (pos-- > 0 && current != null) {
      last = current;
      current = current.next;
    }
    if (current == null && pos >= 0) {
      return pre.next;
    }
    // To handle last node insertion (# of pointers involed newNode (2) , last
    // (1) , current(1))
    if (current != null) {
      current.prev = newNode;
      newNode.next = current;
    }
    last.next = newNode;
    newNode.prev = last;
    return pre.next;
  }
}
