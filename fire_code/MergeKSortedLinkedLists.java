import java.util.*;
// Merge k Sorted Linked Lists
// Write a method to merge k Sorted Linked Lists. Why would you ever want to do
// that? Well, if you're dealing with a list of over 200 Million Integers that
// needs to be sorted, an efficient approach might involve splitting up the
// massive list into k smaller lists, sorting each list in memory and then
// combining the sorted lists to re-create the original list, albeit sorted.
// Example:
// Inputs Lists :
// LinkedList1: 1.2.13.20
// LinkedList2: 1.20.35.40
// LinkedList3: 5.6.12.18
// Output List:
// LinkedList: 1.1.2.5.6.12.13.18.20.20.35.40
// Note:
// mergeKLists takes in an ArrayList of ListNodes - lists, where each ListNode
// is the head of a custom Linked List structure.

public class MergeKSortedLinkedLists {
  ListNode mergeTwoLists(ListNode l1, ListNode l2) {
    if (l1 == null) return l2;
    if (l2 == null) return l1;
    if (l1.data <= l2.data) {
      l1.next = mergeTwoLists(l1.next, l2);
      return l1;
    }
    l2.next = mergeTwoLists(l1, l2.next);
    return l2;
  }

  public ListNode mergeKLists(ArrayList<ListNode> lists) {
    if (lists == null || lists.size() == 0) return null;
    int len = lists.size();
    while (len > 1) {
      for (int i = 0; i < len / 2; ++i) {
        // Diff between add(^ size) and set(keep the size same) in List
        lists.set(i, mergeTwoLists(lists.get(i), lists.get(len - 1 - i)));
      }
      len = (len + 1) / 2;
    }
    return lists.get(0);
  }
}
