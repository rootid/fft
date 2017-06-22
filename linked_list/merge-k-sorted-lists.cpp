//Merge k Sorted Lists
//Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
//
//
//NOTE :  push_back, erase are time consuming,
//
//During 1st iteration, we merge two lists(every list is N) into one, this will make K down to K / 2.
//During 2nd iteration, we merge two lists(every list is 2N) into one, this will make K / 2 down to k /4.
//During 3rd iteration, we merge two lists(every list is 4N) into one, this will make K / 4 down to k /8.
//And so forth...
//I think when we merge two lists, the complexity is O(list1.length) + O(list2.length).
//So the total complexity is:
//(2N) * (K / 2) + 
//(4N) * (K / 4) + 
//(8N) * (K / 8) + 
//.............. + 
//(2^logK*N) * (K / (2 ^logK)) 
//= logK*KN
//

//############################################# with helper ############################################# 
ListNode* mergeHelper(ListNode* f,ListNode *s) {
     ListNode *tmp = new ListNode(0);
     while(f || s) {
         if( s == NULL || f->val < s->val) {
             tmp->next = f;
             f = f->next;
         } else if(f == NULL || f->val > s->val) {
             tmp->next = s;
             s = s->next;
         }
     }
     return tmp->next;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
     if(lists.size()  == 0) {
         return NULL;
     }
     if(lists.size() == 1) {
         return lists[0];
     } 
     int sz = lists.size();
     int mid = sz/2;
     vector<ListNode *> fh(lists.begin(),lists.begin()+mid);
     vector<ListNode *> sh(lists.begin()+mid,lists.end());
     ListNode* t1 = mergeKLists(fh);
     ListNode* t2 = mergeKLists(sh);
     return mergeHelper(t1,t2);
 }

//############################################# using mergeTwoLists ############################################# 
ListNode *mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == NULL ) return l2;
    else if (l2 == NULL ) return l1;
    if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
ListNode *mergeKLists(vector<ListNode *> &lists) {
    if (lists.empty()) return NULL;
    int len = lists.size();
    while (len > 1) {
        for (int i = 0; i < len / 2; ++i) {
            lists[i] = mergeTwoLists(lists[i], lists[len - 1 - i]);
        }
        len = (len + 1) / 2;
    }
    
    //return lists.front();
    return lists[0];
}


//1.Heap is a kind of data structure. It is a name for a particular way of storing data that makes certain operations very efficient. We can use a tree or array to describe it.
//
//   18
//  /	\
// 10	 16
/// \   / \
//9  5  8  12
//
//18, 10, 16, 9, 5, 8, 12
//2.Priority queue is an abstract datatype. It is a shorthand way of describing a particular interface and behavior, and says nothing about the underlying implementation.
//####################################### priority queue ################################## 
//priority_queue : we can only get the top element

//####################################### priority queue with Dummy node ^yy}################################## 
ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, compare> q;
        for (auto l : lists) {
            if (l) {
                q.push(l);
            }
        }
        
        ListNode pre(0);
        ListNode *node = &pre;
        while (q.size()) {
            ListNode *top = q.top();
            q.pop();
            node->next = top;
            node = node->next;
            if (top->next) {
                q.push(top->next);
            }
        }
        return pre.next;
    }
    
    struct compare {
        bool operator()(const ListNode* l1, const ListNode* l2) {
            return l1->val > l2->val;
        }
};

//##################################### priority_queue : with no dummy node  ##################################### 
struct compare {
    bool operator()(const ListNode* l, const ListNode* r) {
        return l->val > r->val;
    }
};
ListNode *mergeKLists(vector<ListNode *> &lists) { //priority_queue
    priority_queue<ListNode *, vector<ListNode *>, compare> q;
    for(auto l : lists) {
        if(l)  q.push(l);
    }
    if(q.empty())  return NULL;

    ListNode* result = q.top();
    q.pop();
    if(result->next) q.push(result->next);
    ListNode* tail = result;            
    while(!q.empty()) {
        tail->next = q.top();
        q.pop();
        tail = tail->next;
        if(tail->next) q.push(tail->next);
    }
    return result;
}

//####################################### make_heap  ################################## 
//make_heap: we can access all the elements
static bool heapComp(ListNode* a, ListNode* b) {
        return a->val > b->val;
}
ListNode* mergeKLists(vector<ListNode*>& lists) { //make_heap
    ListNode head(0);
    ListNode *curNode = &head;
    vector<ListNode*> v;   
    for(int i =0; i<lists.size(); i++){
        if(lists[i]) v.push_back(lists[i]);
    }
    make_heap(v.begin(), v.end(), heapComp); //vector -> heap data strcture

    while(v.size()>0){
        curNode->next=v.front();
        pop_heap(v.begin(), v.end(), heapComp); 
        v.pop_back(); 
        curNode = curNode->next;
        if(curNode->next) {
            v.push_back(curNode->next); 
            push_heap(v.begin(), v.end(), heapComp);
        }
    }
    return head.next;
}

//################################## pytonic hack  ################################## 
//"I figured out that OJ converts Python list into a ListNode automatically"
//I think what really happens is that the OJ serializes the result to a string, and both Python lists and ListNode lists look the same when serialized (if they have the same contents).
//In any case, I think it's bad to exploit this. It's wrong, 
//and it makes your solutions incomparable to those that do it right.
//class Solution(object):
//    def mergeKLists(self, lists):
//        res = []
//        for l in lists:
//            while l:
//                res.append((l.val, l))
//                l = l.next
//        
//        res.sort(key=lambda tup: tup[0])
//        
//        dummy = ListNode(None)
//        cur = dummy
//        
//        for l in res:
//            cur.next = l[1]
//            cur = cur.next
//        
//        return dummy.next
