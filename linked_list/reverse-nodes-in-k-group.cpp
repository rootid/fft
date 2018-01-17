//Reverse Nodes in k-Group
//Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
//k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
//You may not alter the values in the nodes, only nodes itself may be changed.
//Only constant memory is allowed.
//For example,
//Given this linked list: 1->2->3->4->5
//For k = 2, you should return: 2->1->4->3->5
//For k = 3, you should return: 3->2->1->4->5
//-1 -> 1 -> 2 -> 3 -> 4 -> 5
// |    |    |    | 
//pre  cur  nex  tmp
//-1 -> 2 -> 1 -> 3 -> 4 -> 5
// |         |    |    | 
//pre       cur  nex  tmp
//-1 -> 3 -> 2 -> 1 -> 4 -> 5
// |              |    |    | 
//pre            cur  nex  tmp


ListNode* reverseKGroup(ListNode* head, int k) {
     if(head == NULL|| k== 1) {
       return head;
     }
     int len =0;
     ListNode *preheader = new ListNode(-1);
     preheader->next = head;
     ListNode *cur = preheader, *nex, *tmp, *pre = preheader;
     while(cur = cur->next) {
         len++;
     }
     while(len >= k) {
         cur = pre->next;
         nex = cur->next;
         for(int i=1;i<k;i++) {
             tmp= nex->next;
             nex->next = pre->next;
             pre->next = nex;
             cur->next = tmp;
             nex = tmp;
         }
         pre = cur;
         len-=k;
     }
     return preheader->next;
}

ListNode *reverseKGroup(ListNode *head, int k) {
     if(head==NULL||k==1) return head;
     int len=0;
     ListNode *preheader = new ListNode(-1);
     preheader->next = head;
     ListNode *cur = preheader, *nex, *pre = preheader;
     while(cur = cur->next) 
         len++;
     while(len>=k) {
         cur = pre->next;
         nex = cur->next;
         for(int i=1;i<k;++i) {
             cur->next=nex->next;
             nex->next=pre->next;
             pre->next=nex;
             nex=cur->next;
         }
         pre = cur;
         len-=k;
     }
     return preheader->next;
}

//To not leak memory and to not have to delete preheader manually, you could just do this:
//    ListNode preheader(-1);
//    preheader.next = head;
//    ListNode *cur = &preheader, *nex, *tmp, *pre = &preheader;
//    .
//    .
//    return preheader.next;
