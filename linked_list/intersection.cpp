//Intersection of Two Linked Lists
//Write a program to find the node at which the intersection of two singly linked lists begins.
//For example, the following two linked lists:
//A:          a1 → a2
//                   ↘
//                     c1 → c2 → c3
//                   ↗            
//B:     b1 → b2 → b3
//begin to intersect at node c1.
//Notes:
//If the two linked lists have no intersection at all, return null.
//The linked lists must retain their original structure after the function returns.
//You may assume there are no cycles anywhere in the entire linked structure.
//Your code should preferably run in O(n) time and use only O(1) memory.
//
//

//UGLY 
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
     int l1 = 0;
     int l2 = 0;
     ListNode *h1 = headA;
     ListNode *h2 = headB;
     while(h1 != nullptr) {
         l1++;
         h1 = h1->next;
     }
     while(h2 != nullptr) {
         l2++;
         h2 = h2->next;
     }
     int t = abs(l1-l2);
     h1 = headA;
     h2 = headB;
     if(l2 > l1) {
         h1 = headB;
         h2 = headA;
     }
     while(t != 0) {
         h1 = h1->next;
         t--;
     }
     while(h1 != NULL && h2 != NULL) {
         if(h1 == h2) {
             return h1;
         }
         h1 = h1->next;
         h2 = h2->next;
     }
     return nullptr;
 }


//GOOD
// Issue : whenever there is no intersection ,path will be visited twice.
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
  if (headA == NULL || headB == NULL)  {
    return NULL; 
  }
  ListNode* h1 = headA;
  ListNode* h2= headB;
  while (h1 != h2) {
      h1 = h1->next;
      h2 = h2->next;
      if (h1 == h2)  {
        return h1; // in case h1 == h2 == null
      }
      if (h1 == NULL) { //SWAP both pointers 
        h1 = headB;
      }
      if (h2 == NULL) { 
        h2 = headA; 
      }
  }
  return h1;
}
