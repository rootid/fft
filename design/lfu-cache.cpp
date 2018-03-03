//LFU Cache
//Design and implement a data structure for Least Frequently Used (LFU) cache.
//It should support the following operations: get and put.
//get(key) - Get the value (will always be positive) of the key if the key
//exists in the cache, otherwise return -1.
//put(key, value) - Set or insert the value if the key is not already present.
//When the cache reaches its capacity, it should invalidate the least
//frequently used item before inserting a new item. For the purpose of this
//problem, when there is a tie (i.e., two or more keys that have the same
//frequency), the least recently used key would be evicted.
//Follow up:
//Could you do both operations in O(1) time complexity?
//Example:
//LFUCache cache = new LFUCache( 2 /* capacity */ );
//cache.put(1, 1);
//cache.put(2, 2);
//cache.get(1);       // returns 1
//cache.put(3, 3);    // evicts key 2
//cache.get(2);       // returns -1 (not found)
//cache.get(3);       // returns 3.
//cache.put(4, 4);    // evicts key 1.
//cache.get(1);       // returns -1 (not found)
//cache.get(3);       // returns 3
//cache.get(4);       // returns



//      Increasing frequencies
//  ----------------------------->
//
//+------+    +---+    +---+    +---+
//| Head |----| 1 |----| 5 |----| 9 |  Frequencies
//+------+    +-+-+    +-+-+    +-+-+
//              |        |        |
//            +-+-+    +-+-+    +-+-+     |
//            |2,3|    |4,3|    |6,2|     |
//            +-+-+    +-+-+    +-+-+     | Most recent
//                       |        |       |
//                     +-+-+    +-+-+     |
// key,value pairs     |1,2|    |7,9|     |
//                     +---+    +---+     v


//######################################### 3 Maps #########################################
//1 the least recently+frequently used value to be removed is the first element
//in LinkedHashSet with the lowest count/frequency.
//2. min is used to track the group of elements with least frequency
//3. lists maps frequency to groups, each element in same group has the same
//count
public class LFUCache {

    private int min;

    private final int capacity;
    private final HashMap<Integer, Integer> keyToVal;
    private final HashMap<Integer, Integer> keyToCount;
    private final HashMap<Integer, LinkedHashSet<Integer>> countToLRUKeys;

    public LFUCache(int capacity) {
        this.min = -1;
        this.capacity = capacity;
        this.keyToVal = new HashMap<>();
        this.keyToCount = new HashMap<>();
        this.countToLRUKeys = new HashMap<>();
    }

    public int get(int key) {
        if (!keyToVal.containsKey(key)) return -1;

        int count = keyToCount.get(key);
        countToLRUKeys.get(count).remove(key); // remove key from current count (since we will inc count)
        if (count == min && countToLRUKeys.get(count).size() == 0) min++; // nothing in the current min bucket

        putCount(key, count + 1);
        return keyToVal.get(key);
    }

    public void put(int key, int value) {
        if (capacity <= 0) return;

        if (keyToVal.containsKey(key)) {
            keyToVal.put(key, value); // update key's value
            get(key); // update key's count
            return;
        }

        if (keyToVal.size() >= capacity)
            evict(countToLRUKeys.get(min).iterator().next()); // evict LRU from this min count bucket

        min = 1;
        putCount(key, min); // adding new key and count
        keyToVal.put(key, value); // adding new key and value
    }

    private void evict(int key) {
        countToLRUKeys.get(min).remove(key);
        keyToVal.remove(key);
    }

    private void putCount(int key, int count) {
        keyToCount.put(key, count);
        countToLRUKeys.computeIfAbsent(count, ignore -> new LinkedHashSet<>());
        countToLRUKeys.get(count).add(key);
    }
}
//######################################### Priority Queue + HashMap #########################################
class LFUCache {
    Node head = null;
    final int capacity;
    Map<Integer, Integer> valueMap = new HashMap<>();
    Map<Integer, Node> nodeMap = new HashMap<>();

    public Cache(int capacity) {
        this.capacity = capacity;
    }

    public int get(int key) {
        if (nodeMap.containsKey(key)) increase(key);
        return valueMap.getOrDefault(key, -1);
    }

    public void put(int key, int value) {
        if (0 == this.capacity) return;
        if (Objects.nonNull(valueMap.put(key, value))) increase(key);
        else {
            if (nodeMap.size() == this.capacity) remove();
            add(key);
        }
    }

    private void increase(int key) {
        Node node = nodeMap.get(key);
        node.keys.remove(key);
        if (Objects.isNull(node.next)) node.next = new Node(node, null, node.count + 1, key);
        else if (node.next.count == node.count + 1) node.next.keys.add(key);
        else node.next = node.next.prev = new Node(node, node.next, node.count + 1, key);
        nodeMap.put(key, node.next);
        if (node.keys.isEmpty()) remove(node);
    }

    private void remove(Node node) {
        if (head == node) head = node.next;
        else node.prev.next = node.next;
        if (Objects.nonNull(node.next)) node.next.prev = node.prev;
    }

    private void add(int key) {
        if (Objects.isNull(head)) head = new Node(null, null, 1, key);
        else if (head.count == 1) head.keys.add(key);
        else head = head.prev = new Node(null, head, 1, key);
        nodeMap.put(key, head);
    }

    private void remove() {
        int oldest = head.keys.iterator().next();
        head.keys.remove(oldest);
        if (head.keys.isEmpty()) remove(head);
        nodeMap.remove(oldest);
        valueMap.remove(oldest);
    }

    class Node {
        public Node prev, next;
        public final int count;
        public LinkedHashSet<Integer> keys = new LinkedHashSet<>();

        public Node(Node prev, Node next, int count, int key) {
            this.prev = prev;
            this.next = next;
            this.count = count;
            keys.add(key);
        }
    }
}
//######################################### Priority Queue + HashMap #########################################
//PriorityQueue + HashMap: put O(capacity) get O(capacity))
//Operations involved 1. Search in PQ 2. Insert in PQ 3. Delete in PQ
//NOTE : Heap search requires O(n)
long stamp;
int capacity;
int num;
PriorityQueue<Pair> minHeap;
HashMap<Integer, Pair> hashMap;

// @param capacity, an integer
public LFUCache(int capacity) {
    // Write your code here
    this.capacity = capacity;
    num = 0; //not required
    minHeap = new PriorityQueue<Pair>();
    hashMap = new HashMap<Integer, Pair>();
    stamp = 0;
}

// @param key, an integer
// @param value, an integer
// @return nothing
public void put(int key, int value) {
    if (capacity == 0) {
        return;
    }
    // Write your code here
    if (hashMap.containsKey(key)) {
        Pair old = hashMap.get(key);
        minHeap.remove(old);

        Pair newNode = new Pair(key, value, old.times + 1, stamp++);

        hashMap.put(key, newNode);
        minHeap.offer(newNode);
    } else if (num == capacity) {
        Pair old = minHeap.poll();
        hashMap.remove(old.key);

        Pair newNode = new Pair(key, value, 1, stamp++);

        hashMap.put(key, newNode);
        minHeap.offer(newNode);
    } else {
        num++;
        Pair pair = new Pair(key, value, 1, stamp++);
        hashMap.put(key, pair);
        minHeap.offer(pair);
    }
}

public int get(int key) {
    if (capacity == 0) {
        return -1;
    }
    // Write your code here
    if (hashMap.containsKey(key)) {
        Pair old = hashMap.get(key);
        minHeap.remove(old);

        Pair newNode = new Pair(key, old.value, old.times + 1, stamp++);

        hashMap.put(key, newNode);
        minHeap.offer(newNode);
        return hashMap.get(key).value;
    } else {
        return -1;
    }
}

class Pair implements Comparable<Pair> {
    long stamp;
    int key;
    int value;
    int times;
    public Pair(int key, int value, int times, long stamp) {
        this.key = key;
        this.value = value;
        this.times = times;
        this.stamp = stamp;
    }

    public int compareTo(Pair that) {
		//First frquency compare and then age bit compare
        if (this.times == that.times) {
            return (int)(this.stamp - that.stamp);
        } else {
            return this.times - that.times;
        }
    }
}

//######################################### Sorting #########################################
class LFUCache {
 public:
  struct LRUNode {
    int freq;
    list<pair<int, int> > vals; //k,v
    LRUNode(int f = 0) : freq(f) { }
  };
  typedef list<LRUNode>::iterator iptr; //-------> sort by freq
  typedef list<pair<int, int> >::iterator jptr;   // | sort by TS

  LFUCache(int capacity) {
    capacity_ = capacity;
  }

  int get(int key) {
    int val = -1;
    if (kv_.find(key) != kv_.end()) {
      kv_[key] = promote(key);
      val = kv_[key].second->second;
    }
    return val;
  }

  void put(int key, int value) {
    if (capacity_ <= 0) return;
    if (kv_.find(key) == kv_.end()) {
      if (kv_.size() == capacity_) {
        evict();
      }
      kv_[key] = insert(key, value);
    } else {
      kv_[key] = promote(key, value);
    }
  }
 private:
  pair<iptr, jptr> promote(int key, int val = -1) {
    iptr i; jptr j;
    tie(i, j) = kv_[key];
    iptr k = next(i);
    if (val < 0) val = j->second;
    int freq = i->freq + 1;
    i->vals.erase(j);
    if (i->vals.empty())
      cache_.erase(i);
    if (k == cache_.end() || k->freq != freq)
      i = cache_.insert(k, LRUNode(freq));
    else i = k;
    j = i->vals.insert(i->vals.end(), {key, val});
    return {i, j};
  }

  void evict() {
    iptr i = cache_.begin();
    jptr j = i->vals.begin();
    kv_.erase(j->first);
    i->vals.erase(j);
    if (i->vals.empty()) {
      cache_.erase(i);
    }
  }

  pair<iptr, jptr> insert(int key, int val) {
    iptr i = cache_.begin();
    if (i == cache_.end() || i->freq != 1) //first ele/new ele
      i = cache_.insert(i, LRUNode(1));
    jptr j = i->vals.insert(i->vals.end(), {key, val});
    return {i, j};
  }
 private:
  list<LRUNode> cache_; //ith idx -> freq
  int capacity_;
  unordered_map<int, pair<iptr, jptr> > kv_; //kv + indices (i,j pos) refer insert
};
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

//########################################################## HashTable + BST  ##########################################################
struct CacheNode{
    int key;
    int val;
    int freq;
    CacheNode(int k, int v):freq(1), key(k), val(v){}
};

struct Compare{
    bool operator()(const CacheNode& a, const CacheNode& b){
        return a.freq < b.freq;
    }
};

class LFUCache {
public:
    LFUCache(int capacity) {
        size = capacity;
    }

    int get(int key) {
        auto it = cacheMap.find(key);
        if (size == 0 || it == cacheMap.end()) return -1;
        CacheNode temp = *(it->second);
        temp.freq++;
        cacheSet.erase(it->second);
        cacheMap[key] = cacheSet.insert(temp);
        return temp.val;
    }

    void set(int key, int value) {
        if(size == 0) return;
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()){
            if(cacheMap.size() == size){
                cacheMap.erase((cacheSet.begin())->key);
                cacheSet.erase(cacheSet.begin());
            }
            CacheNode temp = CacheNode(key, value);
            cacheMap[key] = cacheSet.insert(temp);
            return;
        }
        CacheNode temp = *(it->second);
        temp.freq++;
        temp.val = value;
        cacheSet.erase(it->second);
        cacheMap[key] = cacheSet.insert(temp);
    }

private:
    int size;
    std::multiset<CacheNode, Compare> cacheSet; //sort based on frquencies
    unordered_map<int, std::multiset<CacheNode, Compare>::iterator> cacheMap;
};

//######################## with PQ ########################

class LFUCache {
public:
    struct Node {
        int key; // key of the element.
        int val; // value of the ement.
        int fre; // usage frequency
        int timeStamp; // the latest time stamp when this element is accessed.
        Node(): key(-1), val(-1), timeStamp(-1), fre(0) {}
        Node(int k, int v, int ts): key(k), val(v), timeStamp(ts), fre(1) {}
    };

    LFUCache(int capacity) {
        Cap = capacity;
        Node* dummy = new Node();
        pq.push_back(dummy); // The pq start from pq[1].
        ts = 0;
    }

    int get(int key) {
        if(!mp.count(key)) return -1;
        int index = mp[key];
        int val = pq[index]->val;
	pq[index]->fre++;
	pq[index]->timeStamp = ++ts;
        sink(index);
        return val;
    }

    void set(int key, int value) {
        if(Cap <= 0) return;
	if(mp.count(key)) {
	   int index = mp[key];
	   pq[index]->val = value;
	   get(key);
	}
	else {
	    if(pq.size() - 1 == Cap) {
	        int oldKey = pq[1]->key;
		mp.erase(oldKey);
		Node* newnode = new Node(key, value, ++ts);
		pq[1] = newnode;
		mp[key] = 1;
		sink(1);
	    }
	    else {
	        Node* newnode = new Node(key, value, ++ts);
		pq.push_back(newnode);
		mp[key] = pq.size() - 1;
		swim(pq.size() - 1);
	    }
	}
    }

private:
	vector<Node*> pq; // A priority queue, with the least usage frequency and least recently used element at the top.
	unordered_map<int, int> mp; // A mapping from the key of the element to its index in the priority queue.
	int Cap; // Capcity of the cache
	int ts; // time-stamp: indicate the time stamp of the latest operation of an element. According to the requirement of LFU cache, when we need to evict an element from the cache, but there are multiple elements with the same minimum frequency, then the least recently used element should be evicted.

    /*
     * Recursively sink a node in priority queue. A node will be sinked, when its frequency is larger than any of its
     * children nodes, or the node has the same frequency with a child, but it is recently updated.
     */
	void sink(int index) {
	    int left = 2 * index, right = 2 * index + 1, target = index;
	    if(left < pq.size() && pq[left]->fre <= pq[target]->fre) // If the left child has the same frequency, we probably need to swap the parent node and the child node, because the parent node is recently accessed, and the left child node was accessed at an older time stamp.
               target = left;
            if(right < pq.size()) {
                if(pq[right]->fre < pq[target]->fre || (pq[right]->fre == pq[target]->fre && pq[right]->timeStamp < pq[target]->timeStamp)) // If right child has the same frequency and an older time stamp, we must swap it.
                     target = right;
		}
		if(target != index) {
		    myswap(target, index);
	            sink(target);
		}
	}

    /*a
     * Recursively swim a node in priority queue. A node will be swimmed, when its frequency is less than its
     * parent node. If the node has the same frequency with its parent, it is not needed to be swimmed, because
     * it is recently accessed.
     */
	void swim(int index) {
	    int par = index / 2;
	    while(par > 0 && pq[par]->fre > pq[index]->fre) {
	        myswap(par, index);
		index = par;
		par /= 2;
	    }
	}

	void myswap(int id1, int id2) {
	    swap(pq[id1], pq[id2]);
	    mp[pq[id1]->key] = id1;
	    mp[pq[id2]->key] = id2;
	}
};

//############################3

class LFUCache {
int capacity_;
typedef list<int> IntList;
struct KeyInfo {
    int val;
    int freq;
    IntList::iterator key_list_iter;
};
unordered_map<int, KeyInfo> key_info_map_;
struct FreqInfo {
    IntList key_list;
    IntList::iterator freq_list_iter;
};
unordered_map<int, FreqInfo> freq_info_map_;
IntList freq_list_;

void updateFreq(KeyInfo& key_info) {
    FreqInfo& old_freq_info = freq_info_map_[key_info.freq];
    IntList& old_key_list = old_freq_info.key_list;
    key_info.freq++;
    FreqInfo& new_freq_info = freq_info_map_[key_info.freq];
    IntList& new_key_list = new_freq_info.key_list;
    new_key_list.splice(new_key_list.begin(), old_key_list, key_info.key_list_iter);
    key_info.key_list_iter = new_key_list.begin();
    if (new_key_list.size() == 1) {
        auto temp_iter = old_freq_info.freq_list_iter;
        temp_iter++;
        new_freq_info.freq_list_iter = freq_list_.insert(temp_iter, key_info.freq);
    }
    if (old_key_list.size() == 0) {
        freq_list_.erase(old_freq_info.freq_list_iter);
    }
}

void evict() {
    int freq_to_evict = freq_list_.front();
    FreqInfo& freq_info = freq_info_map_[freq_to_evict];
    IntList& key_list = freq_info.key_list;
    int key_to_evict = key_list.back();
    key_list.pop_back();
    if (key_list.size() == 0) {
        freq_list_.erase(freq_info.freq_list_iter);
    }
    key_info_map_.erase(key_to_evict);
}

void insert(int key, int value) {
    KeyInfo key_info;
    key_info.val = value;
    key_info.freq = 1;
    FreqInfo& freq_info = freq_info_map_[key_info.freq];
    IntList& key_list = freq_info.key_list;
    key_list.push_front(key);
    key_info.key_list_iter = key_list.begin();
    key_info_map_[key] = key_info;
    if (key_list.size() == 1) {
        freq_list_.push_front(key_info.freq);
        freq_info.freq_list_iter = freq_list_.begin();
    }
}

public:

LFUCache(int capacity) {
    capacity_ = capacity;
}

int get(int key) {
    auto iter = key_info_map_.find(key);
    if (iter != key_info_map_.end()) {
        KeyInfo& key_info = iter->second;
        int val = key_info.val;
        updateFreq(key_info);
        return val;
    } else {
        return -1;
    }
}

void put(int key, int value) {
    auto iter = key_info_map_.find(key);
    if (iter != key_info_map_.end()) {
        KeyInfo& key_info = iter->second;
        key_info.val = value;
        updateFreq(key_info);
        return;
    }
    /* Insert new */
    if (capacity_ == 0) {
        return;
    }
    while (key_info_map_.size() >= capacity_) {
        /* Evict */
        evict();
    }
    insert(key, value);
}
};
//####################################################  Freq + bucket + DLL ####################################################

//LFU cache holds:
//Doubly linked list of buckets sorted by frequency: BucketNode*
//unordered_map<int, pair<BucketNode*, ListNode*>> keyLocationTable
//
//BucketNode holds:
//Doubly linked list of ListNode* ordered by insertion order.
//
//LiskNode holds:
//<key, value> pair
class LFUCache {
private:
    struct ListNode {
        int key;
        int value;
        ListNode* prev;
        ListNode* next;
        ListNode(int k, int v) : key(k), value(v), prev(NULL), next(NULL) {};
    };

    struct BucketNode {
        int freq;
        ListNode* head;
        ListNode* tail;
        BucketNode* prev;
        BucketNode* next;

        BucketNode(int f) : freq(f), prev(NULL), next(NULL), head(NULL), tail(NULL) {};

        void removeOne(ListNode* node) {
            if (node == head && node == tail) {
                tail = head = NULL;
            } else if (node == head) {
                node->next->prev = NULL;
                head = node->next;
            } else if (node == tail) {
                node->prev->next = NULL;
                tail = node->prev;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            node->prev = node->next = NULL;
        }

        void addOne(ListNode* node) {
            if (head == NULL) {
                head = tail = node;
            } else {
                head->prev = node;
                node->next = head;
                head = node;
            }
        }

        bool empty() { return head == NULL; }
    };

public:
    LFUCache(int capacity) : mCapacity(capacity) {
        head = tail = NULL;
    }

    int get(int key) {
        if (mCapacity == 0) return -1;
        ListNode* node = promote(key);
        return node ? node->value : -1;
    }

    void put(int key, int value) {
        if (mCapacity == 0) return;

        ListNode* node = promote(key);
        if (node) {
            node->value = value;
            return;
        } else {
            if (freqTable.size() >= mCapacity) evictLast();
            node = new ListNode(key, value);
            BucketNode* bucket;
            if (tail == NULL || tail->freq != 1) {
                bucket = new BucketNode(1);
                bucket->addOne(node);
                if (tail == NULL) {
                    head = tail = bucket;
                } else {
                    bucket->prev = tail;
                    tail->next = bucket;
                    tail = bucket;
                }
            } else {
                bucket = tail;
                bucket->addOne(node);
            }
            freqTable[key] = pair<BucketNode*, ListNode*>(bucket, node);
        }
    }

private:
    inline ListNode* promote(int key) {
        auto it = freqTable.find(key);
        if (it == freqTable.end()) return NULL;
        BucketNode* bucket = it->second.first;
        ListNode* node = it->second.second;
        bucket->removeOne(node);
        BucketNode* newBucket;
        if (bucket->prev == NULL || bucket->prev->freq != bucket->freq + 1) {
            newBucket = new BucketNode(bucket->freq + 1);
            newBucket->addOne(node);
            if (bucket->prev == NULL) {
                head = newBucket;
                newBucket->next = bucket;
                bucket->prev = newBucket;
            } else {
                bucket->prev->next = newBucket;
                newBucket->prev = bucket->prev;
                newBucket->next = bucket;
                bucket->prev = newBucket;
            }
        } else {
            newBucket = bucket->prev;
            newBucket->addOne(node);
        }

        it->second.first = newBucket;
        it->second.second = node;

        if (bucket->empty()) removeBucket(bucket);

        return node;
    }

    inline void removeBucket(BucketNode* bucket) {
        if (bucket == head && bucket == tail) {
            head = tail = NULL;
        } else if (bucket == head) {
            bucket->next->prev = NULL;
            head = bucket->next;
        } else if (bucket == tail) {
            bucket->prev->next = NULL;
            tail = bucket->prev;
        } else {
            bucket->prev->next = bucket->next;
            bucket->next->prev = bucket->prev;
        }
        delete bucket;
    }

    inline void evictLast() {
        ListNode* node = tail->tail;
        freqTable.erase(node->key);
        tail->removeOne(node);
        delete node;
        if (tail->empty()) removeBucket(tail);
    }

private:
    int mCapacity;
    BucketNode* head;
    BucketNode* tail;
    unordered_map<int, pair<BucketNode*, ListNode*>> freqTable;
};

//################ splice function
//

//FLIST = list<pair<int, int>> is the list save data entry with the same
//frequency count, with list you can easier splice item to next frequency list.
//map<int, pair<int, int>> saves all the data in a map of frequency to list.
//unordered_map<int, pair<int, FLIST::iterator>> index key to pair of frequency
//and list iterator.

class LFUCache {
public:
LFUCache(int capacity) : capacity_(capacity) {
}
int get(int key) {
    if (capacity_ < 1 || idx.count(key) == 0) return -1;
    int f = idx[key].first++;
    dat[f+1].splice(dat[f+1].end(), dat[f], idx[key].second);
    if (dat[f].empty()) dat.erase(f);
    return idx[key].second->second;
}

void put(int key, int value) {
    if (capacity_ < 1) return;
    if (idx.count(key)) {
        int f = idx[key].first++;
        dat[f+1].splice(dat[f+1].end(), dat[f], idx[key].second);
        if (dat[f].empty()) dat.erase(f);
        idx[key].second->second = value;
    } else {
        if (capacity_ == (int)idx.size()) {
            int k = dat.begin()->second.begin()->first;
            idx.erase(k);
            dat.begin()->second.pop_front();
            if (dat.begin()->second.empty()) dat.erase(dat.begin());
        }
        dat[1].push_back({key, value});
        idx[key] = make_pair(1, prev(dat[1].end()));
    }
}

private:
int capacity_;
using FLIST=list<pair<int, int>>;
map<int, FLIST> dat;
unordered_map<int, pair<int, FLIST::iterator>> idx;
};


//#########################################  #########################################
class ListNode(object):
    def __init__(self, key, val):
        self.prev = None
        self.next = None
        self.val = val
        self.key = key

    def connect(self, nextNode):
        self.next = nextNode
        nextNode.prev = self

class LFUCache(object):

    def __init__(self, capacity):
        """

        :type capacity: int
        """
        self.cap = capacity
        self.head = ListNode(None, None)
        self.tail = ListNode(None, None)
        self.head.connect(self.tail)
        #use to record the first ListNode of this count number
        self.cnt = {0: self.tail}
        # key: key , value:[ListNode, visit count]
        self.kv = {None:[self.tail, 0]}

    def moveforward(self, key):
        node, cnt = self.kv[key]
        self.add('tmp', node.val, cnt + 1)
        self.remove(key)
        self.kv[key] = self.kv['tmp']
        self.kv[key][0].key = key
        del self.kv['tmp']

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        if key not in self.kv:
            return -1
        self.moveforward(key)
        return self.kv[key][0].val

    def set(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """
        if self.cap == 0:
            return
        if key in self.kv:
            self.kv[key][0].val = value
            self.moveforward(key)
            return
        if len(self.kv) > self.cap:
            self.remove(self.tail.prev.key)
        self.add(key, value, 0)


    def remove(self, key):
        node, cnt = self.kv[key]
        if self.cnt[cnt] != node:
            node.prev.connect(node.next)
        elif self.kv[node.next.key][1] == cnt:
            node.prev.connect(node.next)
            self.cnt[cnt] = self.cnt[cnt].next
        else:
            node.prev.connect(node.next)
            del self.cnt[cnt]
        del self.kv[key]

    def add(self, key, value, cnt):
        if cnt in self.cnt:
            loc = self.cnt[cnt]
        else:
            loc = self.cnt[cnt - 1]
        node = ListNode(key, value)
        loc.prev.connect(node)
        node.connect(loc)
        self.cnt[cnt] = node
        self.kv[key] = [node, cnt]



# Your LFUCache object will be instantiated and called as such:
# obj = LFUCache(capacity)
# param_1 = obj.get(key)
# obj.set(key,value)
