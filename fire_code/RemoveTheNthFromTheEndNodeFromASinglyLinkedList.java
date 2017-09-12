// Remove the "Nth from the end" Node from a Singly-Linked Lis
// Given a singly-linked list, remove its Nth from the end node.
// Examples:
// 1->2->3->4->5, n=3 ==> 1->2->4->5
// 1->2->3->4->5, n=1 ==> 1->2->3->4
// 1->2->3->4->5, n=5 ==> 2->3->4->5

public class RemoveTheNthFromTheEndNodeFromASinglyLinkedList {
  public ListNode removeNthFromEnd(ListNode head, int n) {
    ListNode slow = head;
    ListNode fast = head;
    int cnt = 0;
    while (cnt++ != n && fast != null) fast = fast.next;
    if (fast == null && cnt >= n) {  // first node
      return slow.next;
    }
    if (fast == null) return head;
    while (fast.next != null) {
      slow = slow.next;
      fast = fast.next;
    }
    slow.next = slow.next.next;
    return head;
  }
}
