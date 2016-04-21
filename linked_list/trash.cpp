
 /***
     * \algorithm
     * 1. deal with validity of k, ensure list length >= 2, k > 0 && k < length;
     * 2. reverse the first part of n - k nodes, remain the whole list linked;
     * 3. reverse the second part of k nodes, remain the whole list linked;
     * 4. reverse the whole list.
     * 
     * e.g.,
     * 3->2->5->9->11->31, k = 2;
     * 1st PASS: 9->5->2->3->31->11
     * 2nd PASS: 11->31->3->2->5->9
     * 
     * O(2n) = O(n) time O(1) auxiliary space;
     **/
    ListNode* rotateReverseTwice (ListNode *head, int k) {
        int len = getListLength (head);
        if (len == 0 || k % len == 0) {
            return head;
        }

        k %= len;
        int n1 = len - k;
        ListNode *part1Head = NULL, *part2Head = NULL;
        ListNode *curr = head, *next;
        while (curr) {
            next = curr -> next;
            if (n1) {
                curr -> next = part1Head;
                part1Head = curr;
                n1--;
            } else {
                curr -> next = part2Head;
                part2Head = curr;
            }

            curr = next;
        }

        /* for part1, part1Head and head; */
        /* for part2, part2Head; */

        head -> next = part2Head;
        head = NULL;
        curr = part1Head;
        while (curr) {
            next = curr -> next;
            curr -> next = head;
            head = curr;
            curr = next;
        }

        return head;
    }


ListNode* rotateRight(ListNode* head, int k) {
    int l = 0;
    ListNode *node = head;
    while (node) {
        l++;
        node = node->next;
    }
    if (!head || k%l == 0)
        return head;
    k %= l;
    ListNode *fast, *slow;
    fast = slow = head;
    for (int i = 0; i < k; i++)
        fast = fast->next;
    while (fast && fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode *res = slow->next;
    slow->next = NULL;
    fast->next = head;
    return res;
}


public ListNode rev(ListNode head, int m, int n){
    //code to reverse from position m to n
    //Probloem   92 - Reverse Linked List II
}

public ListNode rotateRight(ListNode head, int k) {
    //write code to find i (length of linked list)

    // Also take care of simple cases where k>i and head = null

    k = i-k+1;

    head = rev(head,1,k-1);
    head = rev(head,k,i);
    head = rev(head,1,i);


    return head;
}

