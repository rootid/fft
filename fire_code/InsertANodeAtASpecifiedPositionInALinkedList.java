// Given a singly-linked list, implement a method to insert a node at a specific
// position and return the head of the list.
// If the given position is greater than the list size, simply insert the node
// at the end.
// Examples:
// Input List: 1->2->3
// insertAtPosition(1,4,2) ==> 1->4->2->3
//*position=2 means the 2nd node in the list

public class InsertANodeAtASpecifiedPositionInALinkedList {
  public ListNode insertAtPosition(ListNode head, int data, int pos) {
    if (head == null) {
      return new ListNode(data);
    }
    if (pos == 1) {
      ListNode newNode = new ListNode(data);
      newNode.next = head;
      return newNode;
    }
    head.next = insertAtPosition(head.next, data, pos - 1);
    return head;
  }
}
