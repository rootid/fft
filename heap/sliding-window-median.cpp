//Sliding Window Median
//Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
//Examples: 
//[2,3,4] , the median is 3
//[2,3], the median is (2 + 3) / 2 = 2.5
//Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Your job is to output the median array for each window in the original array.
//For example,
//Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
//Window position                Median
//---------------               -----
//[1  3  -1] -3  5  3  6  7       1
// 1 [3  -1  -3] 5  3  6  7       -1
// 1  3 [-1  -3  5] 3  6  7       -1
// 1  3  -1 [-3  5  3] 6  7       3
// 1  3  -1  -3 [5  3  6] 7       5
// 1  3  -1  -3  5 [3  6  7]      6
//Therefore, return the median sliding window as [1,-1,-1,3,5,6].
//Note: 
//You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.


//####################################### Hightly optimized ############################## 
//Keep the window elements in a multiset and keep an iterator pointing to the middle value
//Speculative mid update based on last nums[i-k] and current value nums [i] 
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int> window(nums.begin(), nums.begin() + k);
    auto mid = next(window.begin(), k / 2);
    vector<double> medians;
    for (int i=k; ; i++) {

        // Push the current median.
        medians.push_back((double(*mid) + *prev(mid, 1 - k%2)) / 2); //1-0 = 1 (even)| 1 - 1 = 0 (odd)

        // If all done, return.
        if (i == nums.size()) {
            return medians;
        }
        // Insert nums[i].
        window.insert(nums[i]);
        if (nums[i] < *mid) {  //1 2 3 //[3 2 1 -1]
            mid--;
        }
        // Erase nums[i-k].
        if (nums[i-k] <= *mid) {
            mid++;
        }
        window.erase(window.lower_bound(nums[i-k])); //erase first occurance of nums[i-k]
    }
}
//##################################### BST + optimized ##################################### 
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int> window;
    vector<double> ret;
    for (int i = 0; i < nums.size(); i++) {
        window.insert(nums[i]);
        if (window.size() < k)  continue;
        auto it1 = window.begin(), it2 = it1;
        advance(it1, (k-1)/2);
        it2 = it1;
        advance(it2, (k & 1) == 0); // if even increase by 1
        ret.push_back((long(*it1) + *it2) / 2.0);
        window.erase(window.find(nums[i-k+1])); //remove the old element
    }
    return ret;
}

//##################################### BST ##################################### 
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int> mp;
    vector<double> med;
    
    //k-1 element inserted
    for(int i=0; i<k-1; ++i) {
      mp.insert(nums[i]);
    }
    
    for(int i=k-1; i< nums.size(); ++i){
        mp.insert(nums[i]); // Add the next number
        
        auto itb = mp.begin(); 
        advance(itb, (k-1)/2); //Find the lower median
        auto ite = mp.end(); 
        advance(ite, -(k+1)/2); //Find the upper median //Note : while going from end iterator increase by 1
    
        double avg = ((long)(*itb) + (*ite)) / 2.0;
        med.push_back(avg);
    
        mp.erase(mp.find(nums[i-k+1])); //Remove the oldest element
    }
    
    return med;
}
