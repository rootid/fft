//Insert Delete GetRandom O(1)
//Design a data structure that supports all following operations in average O(1) time.
//insert(val): Inserts an item val to the set if not already present.
//remove(val): Removes an item val from the set if present.
//getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
//Example:
//// Init an empty set.
//RandomizedSet randomSet = new RandomizedSet();
//// Inserts 1 to the set. Returns true as 1 was inserted successfully.
//randomSet.insert(1);
//// Returns false as 2 does not exist in the set.
//randomSet.remove(2);
//// Inserts 2 to the set, returns true. Set now contains [1,2].
//randomSet.insert(2);
//// getRandom should return either 1 or 2 randomly.
//randomSet.getRandom();
//// Removes 1 from the set, returns true. Set now contains [2].
//randomSet.remove(1);
//// 2 was already in the set, so return false.
//randomSet.insert(2);
//// Since 1 is the only number in the set, getRandom always return 1.
//randomSet.getRandom();
////

//######################################### Map + List ######################################### 
//1. Use map and list
//2. Use list for random function
class RandomizedSet {

    Map<Integer,Integer> valueIdxMap;
    List<Integer> valueList;
    Random random;
    
    /** Initialize your data structure here. */
    public RandomizedSet() {
        valueIdxMap = new HashMap<>();
        valueList = new ArrayList<>();
        random = new Random();
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    public boolean insert(int val) {
        if(valueIdxMap.containsKey(val)) return false;
        valueList.add(val);
        valueIdxMap.put(val, valueList.size() -1);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    public boolean remove(int val) {
          if(!valueIdxMap.containsKey(val)) return false;
          int idxReadyToUse = valueIdxMap.get(val);
          
          valueList.set(idxReadyToUse,valueList.get(valueList.size() -1));
          valueIdxMap.put(valueList.get(idxReadyToUse), idxReadyToUse);
            
          //Remove last element
          valueList.remove(valueList.size() -1);
          valueIdxMap.remove(val);
          return true;
    }
    
    /** Get a random element from the set. */
    //Must act on the index
    public int getRandom() {
        return valueList.get(random.nextInt(valueList.size()));
    }
}



class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (cntr_map.count(val) ) {
            return false;
        }
        v_list.push_back(val);
        cntr_map[val] = v_list.size()-1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (!cntr_map.count(val) ) {
            return false;
        }
        int last_v = v_list.back();
        int c_idx = cntr_map[val];
        v_list[c_idx] = last_v;
        cntr_map[last_v] = c_idx;
        v_list.pop_back();
        cntr_map.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() { 
      return v_list[ rand() % v_list.size() ];
    }
    
    private :
        //keep track of # and idx
        unordered_map<int,int> cntr_map;
        vector<int> v_list;
};
/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
