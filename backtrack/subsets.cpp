//Subsets
//Given a set of distinct integers, nums, return all possible subsets.
//Note:
//Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets.
//For example,
//If nums = [1,2,3], a solution is:
//[
//  [3],
//  [1],
//  [2],
//  [1,2,3],
//  [1,3],
//  [2,3],
//  [1,2],
//  []
//]

#include<iostream>
#include<vector>
using namespace std;

void subsetHelper(vector<int>& nums,choices,level,result) {

}

vector<vector<int>> subsets(vector<int>& nums) {
  
  vector< vector<int> > result;
  bool choices[] = {false,false};
  int level = 0;
  subsetHelper(nums,choices,level,result);
  return result;
}

int main() {

}


//The characteristics of C++ reference is an outstanding tool for backtracking algorithm!
//
//let us use [1,2,3,4] as an example to explain my solution:
//
//subsets([1,2,3,4]) = []
//                     // push(1)
//                     [1, subsets([2,3,4])] // if push N times in subsets([2,3,4]), the pop times is also N, so vec is also [1] after backtrack.
//                     // pop(), push(2)
//                     [2, subsets([3,4])]
//                     // pop(), push(3)
//                     [3, subsets([4])]
//                     // pop(), push(4)
//                     [4, subsets([])]
//                     // pop()
//
//
// think it is O(2^n), you can calculate the total push times as follow:
//
//t(0) = 0
//t(1) = 1+t(0)
//t(2) = 2+t(1)+t(0)
//...
//t(n-1) = n-1+t(n-2)+t(n-3)+...+t(1)+t(0)
//t(n) = n+t(n-1)+t(n-2)+...+t(1)+t(0) = n+t(n-1)+t(n-1)-n+1=2t(n-1)+1
//
//=> t(n)+1 = 2(t(n-1)+1) => t(n)+1 = 2^n => t(n) = 2^n-1
//

class Solution {
public:
    std::vector<std::vector<int> > subsets(std::vector<int> &nums) {
		std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int> > res;
		std::vector<int> vec;
		subsets(res, nums, vec, 0);
		return res;
    }
private:
	void subsets(std::vector<std::vector<int> > &res, std::vector<int> &nums, std::vector<int> &vec, int begin) {
		res.push_back(vec);
		for (int i = begin; i != nums.size(); ++i) {
			vec.push_back(nums[i]);
			subsets(res, nums, vec, i + 1);
			vec.pop_back();
		}
	}
};


class Solution {
public:
    std::vector<std::vector<int> > subsetsWithDup(std::vector<int> &nums) {
		std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int> > res;
		std::vector<int> vec;
		subsetsWithDup(res, nums, vec, 0);
		return res;
    }
private:
	void subsetsWithDup(std::vector<std::vector<int> > &res, std::vector<int> &nums, std::vector<int> &vec, int begin) {
		res.push_back(vec);
		for (int i = begin; i != nums.size(); ++i)
			if (i == begin || nums[i] != nums[i - 1]) { 
				vec.push_back(nums[i]);
				subsetsWithDup(res, nums, vec, i + 1);
				vec.pop_back();
			}
	}
};
