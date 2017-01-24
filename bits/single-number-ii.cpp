//Single Number II
//Given an array of integers, every element appears three times except for one, which appears exactly once. Find that single one.
//Note:
//Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

#include "../headers/global.hpp"

int singleNumber(vector<int>& nums) {
    int number = 0;
    int idx;
    const int k = 3;
    vector<int> bit_count(32,0);
    for(auto &c:nums) {
      idx = 0;
      while(idx < 32) {
        if(c & (1 << idx)) { 
          bit_count[idx] += 1;
          bit_count[idx] %= k;
        }
        idx += 1;
      }
    }
    for(int i=0;i<32;i++)  {
      if(bit_count[i] > 0) {
        number |= (1 << i);
      }
    }
    return number;
}


int main() {

}
