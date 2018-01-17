// Given a doubly-linked list, write a method to delete the node at a given
// position (starting from 1 as the head position) and return the modified
// list's head. Do nothing if the input position is out of range.
// Examples:
// 1<=>2<=>3<=>4, pos=6 ==> 1<=>2<=>3<=>4
// 1<=>2<=>3<=>4, pos=3 ==> 1<=>2<=>4
public class DeleteTheNodeAtTheSpecificPositionInADoublyLinkedList {
  public DoublyLinkedNode deleteAtPos(DoublyLinkedNode head, int pos) {
    int count = 0;
    if (head == null) {
      return head;
    }
    DoublyLinkedNode dummyHead = new DoublyLinkedNode(-1);
    dummyHead.next = head;
    head.prev = dummyHead;
    DoublyLinkedNode curr = dummyHead;
    DoublyLinkedNode prev = null;
    while (curr != null && count++ != pos) {
      curr = curr.next;
    }
    if (curr == null) {
      return dummyHead.next;
    }
    curr.prev.next = curr.next;
    return dummyHead.next;
  }
}
