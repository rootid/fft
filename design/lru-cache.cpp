//LRU Cache
//Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.
//get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
//put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
//Follow up:
//Could you do both operations in O(1) time complexity?
//Example:
//LRUCache cache = new LRUCache( 2 /* capacity */ );
//cache.put(1, 1);
//cache.put(2, 2);
//cache.get(1);       // returns 1
//cache.put(3, 3);    // evicts key 2
//cache.get(2);       // returns -1 (not found)
//cache.put(4, 4);    // evicts key 1
//cache.get(1);       // returns -1 (not found)
//cache.get(3);       // returns 3
//cache.get(4);       // returns 4

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

class LRUCache{

private:
    map<int,int> mp;
    map<int,list<int>::iterator> pos;
    list<int> ageList;
    int capacity;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    int get(int key) {
        if(mp.count(key)) { 
          moveToEnd(key); //key exists move the page to end
          return mp[key];
        }
        return -1;
    }
    void put(int key, int value) {
        if(mp.count(key)) {    
            mp[key] = value; //key exists move the page to end
            moveToEnd(key);
        } else if(mp.size()<capacity) {
            mp[key]=value;
            ageList.push_back(key);
            pos[key] = getLast(ageList);
        } else { //evict page
            mp.erase(ageList.front());
            ageList.pop_front();
            mp[key]=value;
            ageList.push_back(key);
            pos[key] = getLast(ageList);
        }

    }
    void moveToEnd(int key) {
        ageList.erase(pos[key]);
        ageList.push_back(key);
        pos[key]= getLast(ageList);
    }
    //Get the end of List
    list<int>::iterator getLast(list<int> &ageList) {
        auto it = ageList.end();
        it--;
        return it;
    }
};
