//Partition List
//Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
//You should preserve the original relative order of the nodes in each of the two partitions.
//For example,
//Given 1->4->3->2->5->2 and x = 3,
//return 1->2->2->4->3->5.

//#########################################  #########################################
ListNode *partition(ListNode *head, int x) {
    ListNode node1(0), node2(0);
    ListNode *p1 = &node1, *p2 = &node2;
    while (head) {
        if (head->val < x) {
            p1 = p1->next = head;
        }
        else {
            p2 = p2->next = head;
        }
        head = head->next;
    }
    p2->next = NULL;
    p1->next = node2.next;
    return node1.next;
}

//#########################################  #########################################
//[2,1], 2 for example, if p2->next = NULL doesn’t exist, it will generate a circle in the end i.e., 1->2->1.
public ListNode partition(ListNode head, int x) {
      ListNode lsThanX = new ListNode(-1);
      ListNode gtThanX = new ListNode(-1);
      ListNode lsThanXHd = lsThanX;
      ListNode gtThanXHd = gtThanX;
      while(head != null) {
          if(head.val >=x )  {
              gtThanX.next = head;
              gtThanX = gtThanX.next;
          } else {
              lsThanX.next = head;
              lsThanX = lsThanX.next;
          }
          head = head.next;
      }
      gtThanX.next = null;  //important! avoid cycle in linked list
      lsThanX.next = gtThanXHd.next;
      return lsThanXHd.next;
}

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
