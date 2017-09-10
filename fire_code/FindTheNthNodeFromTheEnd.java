//Find the Nth Node from the End - Linked List
//Given a singly-linked list, implement the method that returns Nth node from the end of the list.
//You are allowed to use extra memory for this implementation.
//Examples:
//1->2->3->4->5->6, n=2 ==> 5

public class FindTheNthNodeFromTheEnd {
public ListNode findNthNodeFromEnd(ListNode head, int n) {
    if(head == null) return head;
    ListNode dummy = new ListNode(0);
    dummy.next = head;
    head = dummy;
    ListNode fast = head;
    ListNode slow = head;
    while(fast != null && n-- > 0) fast = fast.next;
    if(n > 0) return null;
    while(fast != null) {
        fast = fast.next;
        slow = slow.next;
    }
    return slow;
}
}
