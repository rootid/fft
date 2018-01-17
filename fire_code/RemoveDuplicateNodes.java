
// Remove Duplicate Nodes
// Given a singly-linked list, remove duplicates in the list and return head of
// the list. Target a worst case space complexity of O(n).
// Examples:
// 1->2->2->4->3->1 ==> 1->2->4->3
// 1 ==> 1
//"" ==> ""
public class RemoveDuplicateNodes {
  public ListNode removeDuplicates(ListNode head) {
    Set<Integer> set = new HashSet<>();
    ListNode current = head;
    ListNode prev = null;
    while (current != null) {
      if (set.contains(current.data)) {
        ListNode tmp = current;
        prev.next = current.next;
        tmp = null;
      }
      set.add(current.data);
      prev = current;
      current = current.next;
    }
    return head;
  }
}
