//Two Sum II - Input array is sorted
//Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
//The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
//You may assume that each input would have exactly one solution and you may not use the same element twice.
//Input: numbers={2, 7, 11, 15}, target=9
//Output: index1=1, index2=2
#include "../headers/global.hpp"

//#################### In built binary search #################### 
public int[] twoSum(int[] nums, int target) {
    int len = nums.length;
    for(int i=0;i<len-1;i++) {
        int key = target - nums[i];
        int idx =  Arrays.binarySearch(nums, i+1, len, key);
        if(idx > 0) return new int[] {i+1 ,idx+1};
    }
    return new int[] {-1,-1};
}


//#################### GOOD #################### 
int binary_search(vector<int>& numbers,int start,int end,int target) {
    while(start <= end) {
        int mid = start + (end-start)/2;
        if(target == numbers[mid]) {
            return mid;
        } else if(target < numbers[mid]) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return -1;
}
vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> result {0,0};
    int len = numbers.size();
    int start = 0;
    int end = 0;
    for(int i=0;i<len;i++) {
         int new_target = target - numbers[i];
         result[0] = i+1;
         int next_idx = -1;
         start = i+1;
         end = len-1;
         //Always search forward
         next_idx = binary_search(numbers,start,end,new_target);
         if(next_idx != -1) {
              result[1] = next_idx+1;
              return result;
         }
    }
    return result;
}

//################################### failed 
//Input:
//[0,0,3,4]
//0
//Output:
//[4,0]
//Expected:
//[1,2]
vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> result {0,0};
    int len = numbers.size();
    unordered_map<int,int> idx_cntr;
    for(int i=0;i<len;i++) {
         int new_target = target - numbers[i];
         idx_cntr[ numbers[i] ] = i+1;
         result[0] = i+1;
         if(idx_cntr.count(new_target) != 0 && result[0] != idx_cntr[ new_target ]) {
             result[1] = idx_cntr[ new_target ];
             sort(result.begin(),result.end());
             return result;
         }
    }
    return result;
}

int main() {
  vector<int> ns{5,25,75};
  twoSum(ns,100);
}
