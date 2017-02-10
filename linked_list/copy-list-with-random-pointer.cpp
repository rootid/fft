//Copy List with Random Pointer
//A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
//Return a deep copy of the list.

RandomListNode *copyRandomList(RandomListNode *head) { 
  if (head == NULL) return NULL;
  RandomListNode *newlist = new RandomListNode(head->label);
  RandomListNode *newlistHead = newlist;
  RandomListNode *cur = head;
  unordered_map<RandomListNode*, RandomListNode*> pmap;
  pmap[head] = newlist;
  
  //copy the head to new list
  while(cur->next) {
      cur = cur->next;
      newlist->next = new RandomListNode(cur->label);
      newlist = newlist->next;
      pmap[cur] = newlist;
  }
  cur = head;
  //copy random pointer
  while(cur) {
      if(pmap.count(cur)) {
          newlist = pmap[cur];
          if (cur->random && pmap.count(cur->random)) {
              newlist->random = pmap[cur->random];
          }
      }
      cur = cur->next;
  }
  return newlistHead;
}
