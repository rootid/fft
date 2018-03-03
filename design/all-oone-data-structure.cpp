//All O`one Data Structure
//Implement a data structure supporting the following operations:
//Inc(Key) - Inserts a new key with value 1. Or increments an existing key by
//1. Key is guaranteed to be a non-empty string.
//Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise
//decrements an existing key by 1. If the key does not exist, this function
//does nothing. Key is guaranteed to be a non-empty string.
//GetMaxKey() - Returns one of the keys with maximal value. If no element
//exists, return an empty string "".
//GetMinKey() - Returns one of the keys with minimal value. If no element
//exists, return an empty string "".
//Challenge: Perform all these in O(1) time complexity.

//####################################### 2-d struct to add the keys #######################################

class AllOne {

public:
    /** Initialize your data structure here. */
    AllOne() {

    }
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (strmap.find(key) == strmap.end()) {
            if (matrix.empty() || matrix.back().val != 1) {
                auto newrow = matrix.emplace(matrix.end(), key, 1);
                strmap[key] = make_pair(newrow, newrow->strs.begin());
            } else {
                auto newrow = --matrix.end();
                newrow->strs.push_front(key);
                strmap[key] = make_pair(newrow, newrow->strs.begin());
            }
        } else {
            auto row = strmap[key].first;
            auto col = strmap[key].second;
            auto lastrow = row;
            --lastrow;
            if (lastrow == matrix.end() || lastrow->val != row->val + 1) {
                auto newrow = matrix.emplace(row, key, row->val + 1);
                strmap[key] = make_pair(newrow, newrow->strs.begin());
            } else {
                auto newrow = lastrow;
                newrow->strs.push_front(key);
                strmap[key] = make_pair(newrow, newrow->strs.begin());
            }
            row->strs.erase(col);
            if (row->strs.empty()) matrix.erase(row);
        }
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (strmap.find(key) == strmap.end()) {
            return;
        } else {
            auto row = strmap[key].first;
            auto col = strmap[key].second;
            if (row->val == 1) {
                row->strs.erase(col);
                if (row->strs.empty()) matrix.erase(row);
                strmap.erase(key);
                return;
            }
            auto nextrow = row;
            ++nextrow;
            if (nextrow == matrix.end() || nextrow->val != row->val - 1) {
                auto newrow = matrix.emplace(nextrow, key, row->val - 1);
                strmap[key] = make_pair(newrow, newrow->strs.begin());
            } else {
                auto newrow = nextrow;
                newrow->strs.push_front(key);
                strmap[key] = make_pair(newrow, newrow->strs.begin());
            }
            row->strs.erase(col);
            if (row->strs.empty()) matrix.erase(row);
        }
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        return matrix.empty() ?  "" : matrix.front().strs.front();
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        return matrix.empty() ?  "" : matrix.back().strs.front();
    }

private :
    struct Row {
        list<string> strs;
        int val;
        Row(const string &s, int x) : strs({s}), val(x) {}
    };
    unordered_map<string, pair<list<Row>::iterator, list<string>::iterator>> strmap;//record <key, <row_iterator, column_iterator> to find the key in O(1)
    list<Row> matrix;
};

//####################################### Hashmap  #######################################
class AllOne {
public:
    AllOne() {
        max_value = 0;
    }
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        unordered_map<string,int>::iterator it = kv.find(key);
        int value = (it == kv.end() ? 0 : it->second);
        // allocate enough spaces for index.
        while (index.size() <= value + 1) {
            index.push_back(unordered_set<string>());
        }
        index[value].erase(key);
        value++;
        index[value].insert(key);
        kv[key] = value;
        if (value > max_value) {
            max_value = value;
        }
        reset_min_value(value);
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        unordered_map<string,int>::iterator it = kv.find(key);
        if (it == kv.end()) {
            return;
        }
        int value = it->second;
        kv.erase(key);
        index[value].erase(key);
        value--;
        if (value > 0) {
            kv[key] = value;
            index[value].insert(key);
        }
        if (value < max_value && index[max_value].size() == 0) {
            max_value--;
        }
        reset_min_value(value);
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (max_value == 0) {
            return "";
        }
        return *(index[max_value].begin());
    }
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (min_value == 0) {
            return "";
        }
        unordered_set<string>::iterator it = index[min_value].begin();
        if (it == index[min_value].end()) {
            return "";
        } else {
            return *it;
        }
    }
private:
    unordered_map<string,int> kv; //inc + dec O(1)
    vector<unordered_set<string> > index; //min/max key
//array with keys as reversed index in order to save every value and keys have
//that value.
//Some one may say that I used a loop to modify minKey/maxKey, but the cost is
//shared equally when we made the position gap between the 'missed'
//minKey/maxKey and the new one.
    int max_value;
    int min_value;
    void reset_min_value(int value) {
        if (value < min_value) {
            min_value = value;
        }
        if (max_value > 0) {
            while (index[min_value].size() == 0) {
                min_value++;
            }
        }
    }

    void print() {
        cout << "kv:" << endl;
        for (unordered_map<string,int>::iterator it = kv.begin(); it != kv.end(); it++) {
            cout << it->first << " -> " << it->second << endl;
        }
        cout << "index(min:" << min_value << ",max:" << max_value << "):" << endl;
        for (int i = min_value; i <= max_value; i++) {
            if (index[i].size() > 0) {
                cout << i << "->";
                for (unordered_set<string>::iterator it = index[i].begin(); it != index[i].end(); it++) {
                    cout << *it << ",";
                }
                cout << endl;
            }
        }
    }

};

//################################# Assumption hashtable are not O(1) given all collision input  ###############################
//For each value(freq), I have a bucket with all keys which have that value.
// The buckets are in a list, sorted by value. That allows constant time insertion/erasure and iteration to the next higher/lower value bucket. A bucket stores its keys in a hash set for easy constant time insertion/erasure/check (see first two posts here if you're worried). I also have one hash map to look up which bucket a given key is in.
class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {

    }

    void inc(string key) {
        // If the key doesn't exist, insert it with value 0.
        if (!bucketOfKey.count(key)) {
            bucketOfKey[key] = buckets.insert(buckets.begin(), {0, {key}}); //freq,key
        }

        // Insert the key in next bucket and update the lookup.
        auto next = bucketOfKey[key], bucket = next++; //next  : pos inside the buketofKeys
        if (next == buckets.end() || next->value > bucket->value + 1) {
            next = buckets.insert(next, {bucket->value + 1, {}});
        }
        next->keys.insert(key);
        bucketOfKey[key] = next;

        // Remove the key from its old bucket.
        bucket->keys.erase(key);
        if (bucket->keys.empty())
            buckets.erase(bucket);
    }

    void dec(string key) {

        // If the key doesn't exist, just leave.
        if (!bucketOfKey.count(key))
            return;
        // Maybe insert the key in previous bucket and update the lookup.
        auto prev = bucketOfKey[key], bucket = prev--;
        bucketOfKey.erase(key);
        if (bucket->value > 1) {
            if (bucket == buckets.begin() || prev->value < bucket->value - 1)
                prev = buckets.insert(bucket, {bucket->value - 1, {}});
            prev->keys.insert(key);
            bucketOfKey[key] = prev;
        }

        // Remove the key from its old bucket.
        bucket->keys.erase(key);
        if (bucket->keys.empty())
            buckets.erase(bucket);
    }

    string getMaxKey() {
        return buckets.empty() ? "" : *(buckets.rbegin()->keys.begin());
    }

    string getMinKey() {
        return buckets.empty() ? "" : *(buckets.begin()->keys.begin());
    }

private:
    //key : given key
    //value : frquency of key
    struct Bucket { int value; unordered_set<string> keys; };
    list<Bucket> buckets;
    unordered_map<string, list<Bucket>::iterator> bucketOfKey;

};
/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */
