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

//################################## Priority queue ################################## 
public ListNode mergeKLists(ListNode[] lists) {
    if (lists==null||lists.length==0) return null;
    
    PriorityQueue<ListNode> queue = new PriorityQueue<ListNode>(lists.length,(a,b)->a.val-b.val);
    ListNode Dummy=new ListNode(0);
    ListNode tail = Dummy;
    
    for(ListNode node : lists)
    if (node != null){
        queue.add(node);
    }
    
    while(!queue.isEmpty()){
        tail.next=queue.poll();
        tail=tail.next;
        if(tail.next!=null){
            queue.add(tail.next);
        }
    }
    
    return Dummy.next;
}

//######################################### Divide and Conquer ######################################### 
//1.If there is a single list, return it as the result
//2.If there are two lists, return their merged lists as the result
//3.Split the list into two halves, recursively merge the lower half and the upper half, and then return the merge of the two halves as the result
//Let there be n elements on average in all the k lists.
//for n number of items of all lists, k for the number of list
//Time :
//We perform merge log(k) times, and in the worst case merge takes O(nk) time, so the worst case time complexity is O(nklogk).
//Space :
//We perform merge log(k) times, and in the worst case merge takes O(1) space, so the worst case space complexity is O(logk).
public class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        if (lists == null)  return null;
        return mergeKListsHelper(lists, 0, lists.length - 1);
    }
    
    private ListNode mergeKListsHelper(ListNode[] lists, int start, int end) {
        //Recursion base case
        if (start > end)    return null;
        
        //Single list
        if (start == end)   return lists[start];

        //Two lists
        if (end - start == 1)   return mergeTwoLists(lists[start], lists[end]);
        
        //More than two lists, so recursively merge them
        int mid = start + (end - start) / 2;
        ListNode lower = mergeKListsHelper(lists, start, mid);
        ListNode upper = mergeKListsHelper(lists, mid + 1, end);
        return mergeTwoLists(lower, upper);
    }
    
    private ListNode mergeTwoLists(ListNode lower, ListNode upper) {
        //Both lists are empty
        if (lower == null && upper == null)     return null;

        //Either one of the lists is empty
        if (lower == null)  return upper;
        if (upper == null)  return lower;
        
        //Both lists are not empty, so we need to merge them
        ListNode res = new ListNode(0);
        
        ListNode i, j, k;
        i = lower;  j = upper;  k = res;
        
        while (i != null && j != null) {
            if (i.val <= j.val) {
                k.next = new ListNode(i.val);
                i = i.next;
            }
            else {
                k.next = new ListNode(j.val);
                j = j.next;
            }
            k = k.next;
        }
       //Add the left over elements

        while (i != null) {
            k.next = new ListNode(i.val);
            i = i.next;
            k = k.next;
        }
        while (j != null) {
            k.next = new ListNode(j.val);
            j = j.next;
            k = k.next;
        }
        
        //First node is dummy, so return res.next
        return res.next;
    }
}

//######################################### D&C ######################################### 
//I think my code's complexity is also O(nlogk) and not using heap or priority queue, n means the total elements and k means the size of list.
//The mergeTwoLists functiony in my code comes from the problem Merge Two Sorted Lists whose complexity obviously is O(n), n is the sum of length of l1 and l2.
//To put it simpler, assume the k is 2^x, So the progress of combination is like a full binary tree, from bottom to top. So on every level of tree, the combination complexity is n, beacause every level have all n numbers without repetition. The level of tree is x, ie logk. So the complexity is O(nlogk).
//for example, 8 ListNode, and the length of every ListNode is x1, x2,
//x3, x4, x5, x6, x7, x8, total is n.
//on level 3: x1+x2, x3+x4, x5+x6, x7+x8 sum: n
//on level 2: x1+x2+x3+x4, x5+x6+x7+x8 sum: n
//on level 1: x1+x2+x3+x4+x5+x6+x7+x8 sum: n
//total 3n, nlog8
public class Solution {
    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null) return l2;
        if (l2 == null) return l1;

        ListNode head=null;
        ListNode former=null;
        while (l1!=null&&l2!=null) {
            if (l1.val>l2.val) {
                if (former==null) former=l2; else former.next=l2;
                if (head==null) head=former; else former=former.next;
                l2=l2.next;
            } else {
                if (former==null) former=l1; else former.next=l1;
                if (head==null) head=former; else former=former.next;
                l1=l1.next;
            }
        }
        if (l2!=null) l1=l2;
        former.next=l1;
        return head;
        
    }
    
    public ListNode mergeKLists(List<ListNode> lists) {
        if (lists.size()==0) return null;
        if (lists.size()==1) return lists.get(0);
        if (lists.size()==2) return mergeTwoLists(lists.get(0), lists.get(1));
        return mergeTwoLists(mergeKLists(lists.subList(0, lists.size()/2)), 
            mergeKLists(lists.subList(lists.size()/2, lists.size())));
    }
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
