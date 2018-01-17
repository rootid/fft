//Two Sum III - Data structure design
//Design and implement a TwoSum class. It should support the following operations: add and find.
//add - Add the number to an internal data structure.
//find - Find if there exists any pair of numbers which sum is equal to the value.
//For example,
//add(1); add(3); add(5);
//find(4) -> true
//find(7) -> false

//################################ GOOD ##########################
class TwoSum {
public:

    // Add the number to an internal data structure.
	void add(int number) {
	    umap[number]++;
	}

    // Find if there exists any pair of numbers which sum is equal to the value.
	bool find(int value) {
	    //2 nos , value -i ,i
	    for(auto i:umap) {
	        int j = value - i.first;
	        //[add(0),find(0)] : expected false
	        if(umap.count(j) && ( (j != i.first) || i.second > 1) ) {
	            return true;
	        }
	    }
	    return false;
	}
	
private : 
    unordered_map<int,int> umap;

};

//################################ Time Limit EXCEED ##########################
class TwoSum {
public:

    // Add the number to an internal data structure.
	void add(int number) {
	    s.push_back(number);
	}

    // Find if there exists any pair of numbers which sum is equal to the value.
	bool find(int value) {
	    unordered_set<int> finder;
	    for(int i=0;i<s.size();i++) {
	        if(finder.find(value - s[i]) != finder.end()) {
	            return true;
	        }
	        finder.insert(s[i]);
	    }
	    return false;
	}
	
private : 
    vector<int> s;

};


// Your TwoSum object will be instantiated and called as such:
// TwoSum twoSum;
// twoSum.add(number);
// twoSum.find(value);
