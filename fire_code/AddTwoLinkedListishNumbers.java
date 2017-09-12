// Add Two Linked List-ish Numbers
// Given two integers represented as linked-lists, find their sum and return it
// in the form of linked list.
// Note: You can assume that the input integers are non negative and the digits
// stored in the linked lists are in the reverse order. Take a look at the
// examples to understand the format.
// Example:
// Input 1: 1->2->3
// Input 2: 1->2->3
// Output : 2->4->6
// Input 1: 9->9
// Input 2: 9->8
// Output : 8->8->1

public class AddTwoLinkedListishNumbers {

  public static ListNode sumTwoLinkedLists(ListNode input1, ListNode input2) {
    ListNode sum = new ListNode(0);
    ListNode current = sum;
    int carry = 0;
    while (input1 != null || input2 != null || carry > 0) {
      int s = input1 != null ? input1.data : 0;
      s += input2 != null ? input2.data + carry : carry;
      carry = s / 10;
      current.next = new ListNode(s % 10);
      current = current.next;
      if (input1 != null) input1 = input1.next;
      if (input2 != null) input2 = input2.next;
    }
    return sum.next;
  }

  public static ListNode sumTwoLinkedListsUgly(ListNode input1,
                                               ListNode input2) {
    ListNode result = new ListNode(0);
    ListNode current = result;
    int carry = 0;
    while (input1 != null && input2 != null) {
      current.next = new ListNode((input1.data + input2.data + carry) % 10);
      current = current.next;
      carry = (input1.data + input2.data + carry) / 10;
      input1 = input1.next;
      input2 = input2.next;
    }
    while (input1 != null) {
      current.next = new ListNode((input1.data + carry) % 10);
      carry = (input1.data + carry) / 10;
      input1 = input1.next;
      current = current.next;
    }

    while (input2 != null) {
      current.next = new ListNode((input2.data + carry) % 10);
      carry = (input2.data + carry) / 10;
      input2 = input2.next;
      current = current.next;
    }

    if (carry >= 1) {
      current.next = new ListNode(carry);
    }
    return result.next;
  }

}
