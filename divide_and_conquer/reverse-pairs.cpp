//Reverse Pairs
//Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].
//You need to return the number of important reverse pairs in the given array.
//Example1:
//Input: [1,3,2,3,1]
//Output: 2
//Example2:
//Input: [2,4,3,5,1]
//Output: 3
//Note:
//The length of the given array will not exceed 50,000.
//All the numbers in the input array are in the range of 32-bit integer.
//##################################### In place merge sort + iterators #######################################################
//Divide + count + merge
int sort_and_count(vector<int>::iterator begin, vector<int>::iterator end) {
    if (end - begin <= 1) {
        return 0;
    }
    auto mid = begin + (end - begin) / 2;
    //divide
    int count = sort_and_count(begin, mid) + sort_and_count(mid, end);
    for (auto i = begin, j = mid; i != mid; ++i) { //scan all elements between begin and mid
        while (j != end and *i > 2L * *j) { //pair condition
            ++j; // if pair found increase j
        }
        count += j - mid; //count : how much times j moved from mid
    }
    inplace_merge(begin, mid, end);
    return count;
}
int reversePairs(vector<int>& nums) {
    return sort_and_count(nums.begin(), nums.end());
}

//###################################### Use of Merge sort Without iterator ##########################################
private :
    int count;
    void checkCount(vector<int>& nums, int start, int mid, int end){
        // two pointers;
        int l = start, r = mid + 1;
        while(l <= mid && r <= end){
            if((long)nums[l] > (long) 2 * nums[r]){
                count += (mid - l + 1);
                r++;
            } else {
                l++;
            }
        }
       // worst case might be nlog(n) 
        sort(nums.begin() + start, nums.begin() + end + 1);
        return;
        //every step sort
    }
    void mergeSort(vector<int>& nums, int start, int end){
        if(start == end) return;
        int mid = (start + end)/2;
        mergeSort(nums,start, mid);
        mergeSort(nums,mid+1,end);
        checkCount(nums,start,mid,end);
        return;
    }
public:
    int reversePairs(vector<int>& nums) {
        if(nums.empty()) return 0;
        count = 0;
        mergeSort(nums,0,nums.size()-1);
        return count;
    }
  
//######################################################### Fenwick tree ######################################################### 
 class Fenwick {
  private:
  	// tree is one unit shiftd from a virtual vector arr[]
  	vector<long> tree;
  	long lsb(long i) { return i & (-i); }
  public:
  	Fenwick(long size) {
  		tree = vector<long>(size + 1, 0);
  	}
  
  	// the following function sums up arr[0..id]
  	long sum(long id) {
  		id++;
  		long ret = 0;
  		while(id > 0) {
  			ret += tree[id];
  			id -= lsb(id);
  		}
  		return ret;
  	}
  
  	// the following function increases arr[id]
  	void add(long id, long val) {
  		long n = tree.size();
  		id++;
  		while(id < n) {
  			tree[id] += val;
  			id += lsb(id);
  		}
  	}
  
  };
class Solution {
  public:
  	long reversePairs(vector<int>& nums) {
  		vector<long> nums2;
  		for(long i : nums) {
  			nums2.push_back(2*i);
  		}
  
  		sort(nums2.begin(), nums2.end());
  		// order maps the original order to sorted order, it doesn't matter if duplicated is present
  		unordered_map<long, long> order;
  		
  		// binary search result, notice that this is index<->index map 
  		unordered_map<long, long> biorder;
  		long ret = 0;
  		long n = nums.size();
  		for(long i = 0; i < n; ++i) {
  			biorder[i] = lower_bound(nums2.begin(), nums2.end(), nums[i]) - nums2.begin();
  			order[nums2[i]/2] = i;
  		}
  
  		Fenwick fw(n);
  		for(long i = n-1; i>=0; --i) {
  			ret += fw.sum(biorder[i]-1);
  			fw.add(order[nums[i]], 1);
  		}
  		return ret;
  	}
  };

