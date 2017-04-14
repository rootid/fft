//Insert Delete GetRandom O(1) - Duplicates allowed
//Design a data structure that supports all following operations in average O(1) time.
//Note: Duplicate elements are allowed.
//insert(val): Inserts an item val to the collection.
//remove(val): Removes an item val from the collection if present.
//getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
//Example:
//// Init an empty collection.
//RandomizedCollection collection = new RandomizedCollection();
//// Inserts 1 to the collection. Returns true as the collection did not contain 1.
//collection.insert(1);
//// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
//collection.insert(1);
//// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
//collection.insert(2);
//// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
//collection.getRandom();
//// Removes 1 from the collection, returns true. Collection now contains [1,2].
//collection.remove(1);
//// getRandom should return 1 and 2 both equally likely.
//collection.getRandom();

//######################################## map + vector ######################################## 
class RandomizedCollection {
  private:
    unordered_map<int,vector<int> > idx_map;
    vector<pair<int,int> > num_freq_vec; //can shrink and grow

  public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        auto result = idx_map.find(val) == idx_map.end();
        idx_map[val].push_back(num_freq_vec.size()); //insert into map
        num_freq_vec.push_back(pair<int, int>(val, idx_map[val].size() - 1)); //insert into the vector
        return result;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) { 
      //move the last element to element to be deleted
      auto result = idx_map.find(val) != idx_map.end();
      if(result) {
          auto last = num_freq_vec.back(); //get the las position
          idx_map[last.first][last.second] = idx_map[val].back(); //idx_map[val] : last found element
          num_freq_vec[idx_map[val].back()] = last;
          idx_map[val].pop_back(); //remove the elemet
          if(idx_map[val].empty()) idx_map.erase(val);
          num_freq_vec.pop_back();
      }
      return result;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return num_freq_vec[rand() % num_freq_vec.size()].first;
    }
};
/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */


//######################################## multimap + vector ######################################## 
class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool ret = true;
        if(valToIndexMap.find(val) != valToIndexMap.end())
            ret = false;
        vals.push_back(val);
        valToIndexMap.insert(pair<int,int>(val, vals.size()-1));
        return ret;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        auto removeItemIt = valToIndexMap.find(val);

		if (removeItemIt == valToIndexMap.end())
			return false;

		int removeItemIndex = removeItemIt->second;
		auto replaceItemItRange = valToIndexMap.equal_range(vals[vals.size() - 1]);
		unordered_multimap<int, int>::iterator replaceItemIt = replaceItemItRange.first;
		for (auto it = replaceItemItRange.first; it != replaceItemItRange.second; it++){
			if (it->second > replaceItemIt->second){
				replaceItemIt = it;
			}
		}
		replaceItemIt->second = removeItemIndex;
		swap(vals[vals.size() - 1], vals[removeItemIndex]);

		vals.pop_back();
		valToIndexMap.erase(removeItemIt);

		return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        int retIndex = rand() % vals.size();
        return vals[retIndex];
    }
    
private:
    unordered_multimap<int, int> valToIndexMap;
    vector<int> vals;
};


//############################################## map + PQ  ############################################## 
class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {}
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        m[val].push(nums.size());
        nums.push_back(val);
	return m[val].size() == 1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (m[val].empty()) return false;
        int idx = m[val].top();
	m[val].pop();
	if (nums.size() - 1 != idx) {
	    int t = nums.back();
	    nums[idx] = t;
	    m[t].pop();
	    m[t].push(idx);
	}
	nums.pop_back();
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
private:
    vector<int> nums;
    unordered_map<int, priority_queue<int>> m;
};
