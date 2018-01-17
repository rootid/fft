// Given a singly-linked list, reverse the list in pairs.
// Example:
// Given 1->2->3->4,
//			reverseInPairs(1) ==> 2->1->4->3

public class ReverseALinkedListInPairs {
  //############### Recursive ##########################
  public ListNode reverseInPairs(ListNode head) {
    if (head == null || head.next == null) return head;
    ListNode grandChild = reverseInPairs(
        head.next.next);         // head-> (head->next) -> (head->next->next)$
    ListNode child = head.next;  // head->child$
    child.next = head;           // child->head$
    head.next = grandChild;      // child->head->grandChild$
    return child;
  }

  //############### Iterative ##########################
  // NOTE : only swaps data not pointers
  public ListNode reverseInPairsRec(ListNode head) {
    ListNode curr = head;
    while (curr != null && curr.next != null) {
      // Swap data between current and next node
      swap(curr, curr.next);
      // Move pointer by 2 nodes to fetch next pair
      curr = curr.next.next;
    }
    return head;
  }

  private void swap(ListNode a, ListNode b) {
    int temp = a.data;
    a.data = b.data;
    b.data = temp;
  }
}
