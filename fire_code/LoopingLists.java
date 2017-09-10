//Looping Lists : Space complexity O(n)
//Given a singly-linked list, implement a method to check if the list has cycles. The space complexity can be O(n). If there is a cycle, return true otherwise return false. Empty lists should be considered non-cyclic.
//Examples:
//1->2->3->4->1 ==> true
//1->2->3->4 ==> false
public class LoopingLists {

public Boolean isCyclic(ListNode head) {
    if(head == null || head.next == null) return false;
    ListNode fast = head;
    ListNode slow = head;
    while(fast.next != null && fast.next.next != null) {
        fast = fast.next.next;
        slow = slow.next;
        if(fast == slow) {
          return true;
        }
    }
    return false;
}
}
