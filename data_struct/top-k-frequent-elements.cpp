//Given a non-empty array of integers, return the k most frequent elements.
//
//For example,
//Given [1,1,1,2,2,3] and k = 2, return [1,2].
//
//Note: 
//You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
//Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
#include "../headers/global.hpp"

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq_map;
    unordered_map<int,vector<int> > inv_freq_map;
    for(auto i:nums) {
        freq_map[i]++;
    }
    for(auto itr=freq_map.begin();itr != freq_map.end();itr++) {
        cout << " sec # =  " <<  itr->second << " fi # =" << itr->first << endl;
        inv_freq_map[itr->second].push_back(itr->first);
    }
    vector<int> res;
    for(int i=nums.size();i>=1 && k;i--) {
        if(inv_freq_map.count(i) > 0) {
            cout << " inv_count = " << inv_freq_map.count(i) <<  " sz =" << inv_freq_map[i].size()  << endl;
            for(int j=0;j< inv_freq_map[i].size() && k;j++) {
                res.push_back(inv_freq_map[i][j]);
                k--;
            }
        }
    }
    return res;
}

int main() {
  vector<int> n({1,2});
  topKFrequent(n,2);
}
