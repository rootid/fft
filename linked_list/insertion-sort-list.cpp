//Sort a linked list using insertion sort.

///################## with array ################## 
void insertionSort(int a[],int len) {
    for (int i=0;i<len;i++) {
        for (int j=i;j>0;j--) {
            if (a[j] < a[j-1]) {
                swap(a[j],a[j-1]);
            } else {
                break;
            }
        }
    }
}

///################## with Node ################## 
ListNode* insertionSortList(ListNode* head) {
        if (!head) return NULL;
   ListNode *dummy = new ListNode(0), *outer = head;
   dummy->next = head;
   while (outer && outer->next) {
       ListNode *inner = dummy, *temp = NULL;
       while (inner != outer) {
           if (inner->next->val > outer->next->val) {    // find right place to insert
               temp = inner->next;
               inner->next = outer->next;
               outer->next = outer->next->next;
               inner->next->next = temp;
               break;
           }
           inner = inner->next;
       }
       if (inner == outer) outer = outer->next;
   }
   return dummy->next;
}

///################## with Node ################## 
ListNode *insertionSortList(ListNode *head) {
    ListNode* dummy = new ListNode(INT_MIN);
    ListNode* now = head;
    ListNode* pre = nullptr;
    while (now != nullptr) {
        pre = dummy;
        while (pre->next != nullptr && pre->next->val < now->val) {
            pre = pre->next;
        }
        ListNode* preNext = pre->next;
        ListNode* nowNext = now->next;
        pre->next = now;
        now->next = preNext;
        now = nowNext;
    }
    return dummy->next;
}

///################## with Node ################## 
ListNode *insertionSortList(ListNode *head) {
        ListNode* res = new ListNode(-1);
        ListNode* cur = res;
        //head is the current node we are dealing with
        while (head) {
            ListNode *next = head->next;
            cur = res;
            while (cur->next && cur->next->val <= head->val) {
                cur = cur->next;
            }
            //insert the head node into the list
            head->next = cur->next;
            cur->next = head;
            //move forward the head node
            head = next;
        }
        return res->next;
}

//######################################### Python  ######################################### 
def insertionSortList(self, head):
    p = dummy = ListNode(0)
    cur = dummy.next = head
    while cur and cur.next:
        val = cur.next.val
        if cur.val < val:
            cur = cur.next
            continue
        if p.next.val > val:
            p = dummy
        while p.next.val < val:
            p = p.next
        new = cur.next
        cur.next = new.next
        new.next = p.next
        p.next = new
    return dummy.next

//######################################### Python  ######################################### 
def insertionSortList(self, head):
    cur = dummy = ListNode(0)
    while head:
        if cur and cur.val > head.val: 
            cur = dummy
        while cur.next and cur.next.val < head.val: 
            cur = cur.next
        cur.next, cur.next.next, head = head, cur.next, head.next
    return dummy.next


//######################################### JAVA O(N^2) ######################################### 
public ListNode insertionSortList(ListNode head) {
    ListNode helper = new ListNode(0);
    ListNode pre = helper;
    ListNode current = head;
    while(current!=null) {
        pre = helper;
        while(pre.next!=null &&pre.next.val<current.val) {
            pre=pre.next;
        }
        ListNode next=current.next;
        current.next=pre.next;
        pre.next=current;
        current=next;
    }
    return helper.next;
}

//######################################### JAVA O(n^2) ######################################### 
public ListNode insertionSortList(ListNode head) {
	ListNode cur = head;
	ListNode dummy = new ListNode(0), p;
	while (cur != null) {
		//locate the insertion position.
		p = dummy;
		while (p.next != null &&  cur.val > p.next.val) {
			p = p.next;
		}
		//insert between p and p.next.
		ListNode pNext = p.next;
		p.next = cur;
		ListNode next = cur.next;
		cur.next = pNext;
		cur = next;
	}
	return dummy.next;
}
