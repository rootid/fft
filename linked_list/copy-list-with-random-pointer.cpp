//Copy List with Random Pointer
//A linked list is given such that each node contains an additional random pointer which could point to any node in the
//list or null.
//Return a deep copy of the list.


//######################################### Iteration #########################################
public RandomListNode copyRandomList(RandomListNode head) {
    RandomListNode dummyNode = new RandomListNode(42);
    RandomListNode nh = dummyNode;
    Map<RandomListNode, RandomListNode> rndLstMap = new HashMap<>();
    while(head != null) {
        nh.next = new RandomListNode(head.label);
        nh = nh.next;
        rndLstMap.put(head, nh); //Str mping bt (Copied Node, Old Node)
        head = head.next;
    }
    for(RandomListNode oldNode: rndLstMap.keySet()) { //traverse old node
           RandomListNode rndNodeSrc = oldNode.random;
           RandomListNode destNode = rndLstMap.get(oldNode);
           destNode.random = rndLstMap.getOrDefault(rndNodeSrc, null);
    }
    return dummyNode.next;
}

//######################################### Iteration + Modify list(Expand) and Rollback #########################################
    public RandomListNode copyRandomList(RandomListNode head) {
        if(head == null) return null;
        RandomListNode tmp = null;
        RandomListNode iter = head;
        RandomListNode copyRef = new RandomListNode(-1);
        //Expand list
        while(iter != null) {
            tmp = iter.next; //Store the pointer - P1
            iter.next  = new RandomListNode(iter.label); //Append new node
            iter.next.next = tmp; //Connect new next link to P1
            iter = tmp; //Get the stored P1
        }
        //Copy random pointer
        iter = head;
        while(iter != null) {
            if(iter.random != null)
                iter.next.random = iter.random.next;
            iter = iter.next.next;
        }
        tmp = copyRef;
        iter = head;
        while(iter != null) {
            tmp.next = iter.next; //get the copied node - P1
            iter.next = iter.next.next;  //Rollback the old list
            iter = iter.next;  //increment expanded node
            tmp = tmp.next; //increment copied node
        }

        return copyRef.next;
    }


//######################################### Iteration + Map  #########################################
//1. Copy next pointer
//2. Copy random pointer
public RandomListNode copyRandomList(RandomListNode head) {
    RandomListNode dummyNode = new RandomListNode(-1); //Use it to avoid null checks
    RandomListNode tmp = dummyNode;
    RandomListNode cur = head;
    Map<RandomListNode, RandomListNode> rmap = new HashMap<>();
    //Copy next pointer
    while(cur != null) {
        tmp.next  = new RandomListNode(cur.label);
        rmap.put(cur,tmp.next);
        cur = cur.next;
        tmp = tmp.next;
    }
    //Copy random pointer
    cur = head;
    while(cur != null) {
        tmp = rmap.get(cur);
        tmp.random = rmap.get(cur.random);
        //if(cur.random != null && rmap.containsKey(cur.random)) tmp.random = rmap.get(cur.random);
        cur = cur.next;
    }
    return dummyNode.next;
}

//######################################### Iteration  #########################################
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

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
