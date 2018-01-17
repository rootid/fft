
// Given a doubly linked list, implement a method to insert a node at its
// head.Return the head of the list
//.Examples : Insert 1 == > 1 Insert 2 ==> 2 <=> 1 Insert 3 ==> 3 <=> 2 <=> 1
public class InsertANodeAtTheHeadInADoublyLinkedList {
  public DoublyLinkedNode insertAtHead(DoublyLinkedNode head, int data) {
    DoublyLinkedNode tmp = new DoublyLinkedNode(data);
    if (head == null) return tmp;
    tmp.next = head;
    head = tmp;
    return head;
  }
}
