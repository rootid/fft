//Given a collection of integers that might contain duplicates, nums, return all possible subsets.
//Note: The solution set must not contain duplicate subsets.
//For example,
//If nums = [1,2,2], a solution is:
//[
//  [2],
//  [1],
//  [1,2,2],
//  [2,2],
//  [1,2],
//  []
//]
//

#include "../headers/global.hpp"

//we want to insert an element which is a dup, we can only insert it after the newly inserted elements from last step.
//Iterative version
vector<vector<int> > subsetsWithDup(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int> > ret = {{}};
    int size = 0, k = 0;
    for (int i = 0; i < nums.size(); i++) { // # of levels
        if(i >= 1 && nums[i] == nums[i - 1]) {
          k = size;
        } else {
          k = 0;
        }
        size = ret.size();
        for (int j = k; j < size; j++) {
            vector<int> temp = ret[j];
            temp.push_back(nums[i]);
            ret.push_back(temp);
        }
    }
    return ret;
}


//To solve this problem, it is helpful to first think how many subsets are there. If there is no duplicate element, the answer is simply 2^n, where n is the number of elements. This is because you have two choices for each element, either putting it into the subset or not. So all subsets for this no-duplicate set can be easily constructed:
//num of subset
//
//(1 to 2^0) empty set is the first subset
//(2^0+1 to 2^1) add the first element into subset from (1)
//(2^1+1 to 2^2) add the second element into subset (1 to 2^1)
//(2^2+1 to 2^3) add the third element into subset (1 to 2^2)
//....
//(2^(n-1)+1 to 2^n) add the nth element into subset(1 to 2^(n-1))
//Then how many subsets are there if there are duplicate elements? We can treat duplicate element as a spacial element. For example, if we have duplicate elements (5, 5), instead of treating them as two elements that are duplicate, we can treat it as one special element 5, but this element has more than two choices: you can either NOT put it into the subset, or put ONE 5 into the subset, or put TWO 5s into the subset. Therefore, we are given an array (a1, a2, a3, ..., an) with each of them appearing (k1, k2, k3, ..., kn) times, the number of subset is (k1+1)(k2+1)...(kn+1). We can easily see how to write down all the subsets similar to the approach above.

    class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > totalset = {{}};
        sort(S.begin(),S.end());
        for(int i=0; i<S.size();){
            int count = 0; // num of elements are the same
            while(count + i<S.size() && S[count+i]==S[i])  count++;
            int previousN = totalset.size();
            for(int k=0; k<previousN; k++){
                vector<int> instance = totalset[k];
                for(int j=0; j<count; j++){
                    instance.push_back(S[i]);
                    totalset.push_back(instance);
                }
            }
            i += count;
        }
        return totalset;
        }
};

//bit manipulation can solve this too
//How to escape the duplicate? easy! use a sign to mark it:
//this is where this state from "if(j>0&&nums[j]==nums[j-1]&&(i>>(j-1)&1)==0)"
//'nums[j] == nums[j-1]' means the array has a duplicate;
//'i>>(j-1)&1)==0' means the bit manipulation is doing with the duplicate bits!

public List<List<Integer>> subsetsWithDup(int[] nums) {
    Arrays.sort(nums);
    int length = nums.length;
    List<List<Integer>> list = new ArrayList<List<Integer>>();
    for(int i =0; i<(1<<length); i++){
        List<Integer> l = new LinkedList<Integer>();
        boolean duplicate = false;
        for(int j =0; j<length; j++){
            if( (i&(1<<j))!=0 ){
                if(j>0&&nums[j]==nums[j-1]&&(i>>(j-1)&1)==0){
                    duplicate = true;
                    break;
                }
                l.add(nums[j]);
            }
        }
        if( duplicate ==false )
            list.add(l);
    }
    return list;
}


class Solution {
public:
void dfs(vector<vector<int>> &res, vector<int>& pre, vector<int>&nums, int k){
    if (k>=nums.size()) return;
    for (int i=k;i<nums.size();i++){
        if (nums[i]!=nums[i-1] || i==k){
            pre.push_back(nums[i]);
            res.push_back(pre);   // for empty set;
            dfs(res,pre,nums,i+1);
            pre.pop_back();
        }
    }
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    vector<vector<int>> res;
    vector<int> pre;
    res.push_back(pre);   // for empty set;
    dfs(res,pre,nums,0);
    return res;
}
};
