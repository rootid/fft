//Sort Colors
//Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
//Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
//Note:
//You are not suppose to use the library's sort function for this problem.

#include<vector>
#include<iostream>
using namespace std;

void printVec(vector<int>& av) {
  for (auto &i:av) {
    cout << i << " ";
  }
  cout << endl;
}

void sortColors(vector<int>& nums) {
  int count[] = {0,0,0};
  int len = nums.size();
  int startIdx = 0;
  int endIdx = nums.size() -1;
  for(int i=0;i<9;i++) {
    cout << i << " ";
  }
  int countIdx = 0;
  for(int i=0,countIdx;i<len;) {
    while(count[countIdx] != 0) {
      nums[i] = 0;
      i++;
      count[countIdx] -= 1;
    }
    cout << countIdx  << endl;
    countIdx += 1;
  }

  //int currentIdx = startIdx;
  //while(currentIdx < endIdx) {
  //  while(nums[startIdx] == 0 && startIdx < endIdx) {
  //    currentIdx = startIdx;
  //    startIdx += 1;
  //  } 
  //  while(nums[endIdx] == 2 && startIdx < endIdx) {
  //    endIdx -= 1;
  //  } 
  //  while(nums[currentIdx] == 1 && currentIdx < endIdx) {
  //      currentIdx += 1;
  //  }
  //  if(nums[currentIdx] == 0) {
  //    swap(nums[startIdx],nums[currentIdx]);
  //    currentIdx += 1;
  //  } 
  //  if(nums[currentIdx] == 2) {
  //    swap(nums[endIdx],nums[currentIdx]);
  //  } 
  //}
  
}

int main(int argc, char *argv[])
{

  //int a[] = {2,0,0,1,1,1,1,0,2};
  int a[] = {2,0,0,1,1,1,1,0,1};
  vector<int> av(a,a+ sizeof(a)/sizeof(a[0]));
  //printVec(av);
  sortColors(av);
  //printVec(av);
  return 0;
}
