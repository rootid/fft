//Minimum Index Sum of Two Lists
//Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.
//You need to help them find out their common interest with the least list index sum. If there is a choice tie between answers, output all of them with no order requirement. You could assume there always exists an answer.
//Example 1:
//Input:
//["Shogun", "Tapioca Express", "Burger King", "KFC"]
//["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
//Output: ["Shogun"]
//Explanation: The only restaurant they both like is "Shogun".
//Example 2:
//Input:
//["Shogun", "Tapioca Express", "Burger King", "KFC"]
//["KFC", "Shogun", "Burger King"]
//Output: ["Shogun"]
//Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).
//Note:
//The length of both lists will be in the range of [1, 1000].
//The length of strings in both lists will be in the range of [1, 30].
//The index is starting from 0 to the list length minus 1.
//No duplicates in both lists.

//###################################### unordred_map ###################################### 
vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
	unordered_map<string, int> map;
	int res = INT_MAX;
	vector<string> resStr;
	for (int i = 0; i <list1.size(); i++)
		map[list1[i]] = i;
	for (int i = 0; i < list2.size(); i++) {
		if (map.find(list2[i]) != map.end()) {
			//cout << list2[i] << endl;
			int val = map.at(list2[i]) + i;
			if (res > val) {
				if (resStr.size()>0) resStr.pop_back();
				res = val;
				resStr.push_back(list2[i]);
			}
			else if (res == val)
				resStr.push_back(list2[i]);
		}
	}
	return resStr;
}


//###################################### Map  ###################################### 
vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
    int punish = l1.size() + l2.size();  // use n as a punishment for missing in either list;
     map<string, int> m;
     for (int i = 0; i < l1.size(); i++) {
       m[l1[i]] += i - punish;
     }
     for (int j = 0; j < l2.size(); j++) { 
       m[l2[j]] += j - punish;
     }
     map<int, vector<string>> rank; //sorted by int
     for (auto p : m) {
       rank[p.second].push_back(p.first);
     }
     return rank.begin()->second;
}

//The idea is to use sum of index in both list as score for every restaurant ever appeared, but need to manage punishment for not show up in either list.
//
//Use sum of size as a punishment for missing in either list : l1.size() + l2.size();
//Create a map, for every restaurant appear in either list, initialize the score as 2 times punish;
//For every restaurant in every list, remove 1*punish for showing up in 1 list.
//On top of the punishment, don't forget to add indexs as score, the smaller the better.

//rank is defined as: map<int, vector<string>> rank
//        map<int, vector<string>> rank; // use a sorted map rank the restaurants
//        for (auto p : m) {
//            rank[p.second].push_back(p.first);
//        }
//std::map::[key] is an overloaded operator act just the same as java.util.Map.get(key), retrieve the value for the given key.
//The [] will create an default value if the key is not found, in this case rank[p.second] will create an empty vector if p.second is not found as a key in the map rank.
//
//equals:
//
//        map<int, vector<string>> rank; // use a sorted map rank the restaurants
//        for (pair<string, int> p : m) {
//            string restaurant = p.first;
//            int punish = p.second;
//            vector<string> restarauts = rank[punish];
//            restarauts.push_back(restaurant);
//        }
//Please refer to this for more information:
//http://www.cplusplus.com/reference/map/map/operator[]/
//
//
//####################################### pytonic ####################################### 
//
//Say the lists are A and B. 
//Let Aindex[element] be the index of that element in A. 
//For every index, value pair (j, v) in B, we have some candidate sum-of-indexes i + j, where i = Aindex[v] if it exists. 
//If the candidate sum is better, it becomes our new answer; if the candidate sums are the same, then we append to our answer.
//def findRestaurant(self, A, B):
//    Aindex = {u: i for i, u in enumerate(A)}
//    best, ans = 1e9, []
//    for j, v in enumerate(B):
//        i = Aindex.get(v, 1e9)
//        if i + j < best:
//            best = i + j
//            ans = [v]
//        elif i + j == best:
//            ans.append(v)
//    return ans
