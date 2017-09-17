// Check a Linked List for Loops or Cycles With O(1) Space Complexity
// Check if a given linked list has cycles. Try to achieve O(n) runtime with a
// space complexity of O(1). If there is a cycle, return true otherwise return
// false. Consider empty lists as non cyclic.
// Examples:
// 1->2->3->4->1 ==> true
// 1->2->3->4 ==> false

public class Cycle {
  //#### Space : O(k) ####
  public Boolean isCyclic(ListNode head) {
    ListNode slow = head;
    ListNode fast = head;
    while (fast != null && fast.next != null) {
      slow = slow.next;
      fast = fast.next.next;
      if (slow == fast) return true;
    }
    return false;
  }
}
