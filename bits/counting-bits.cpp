//Counting Bits
//
//Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.
//Example:
//For num = 5 you should return [0,1,1,2,1,2].
//Follow up:
//It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
//Space complexity should be O(n).
//Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.
//Hint:
//You should make use of what you have produced already.
//Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
//Or does the odd/even status of the number help you in calculating the number of 1s?

#include "../headers/global.hpp"

//An recurrence for this problem is result[i] = result[i / 2] + i % 2.
//############################################### GOOD ############################################### 
vector<int> countBits(int num) {
    vector<int> result(num+1,0);
    for (int i=1; i<=num; i++) {
      result[i] = result[i >> 1] + (i & 1);
    }
    return result;
}

//O(n) + DP + Pattern-matching
//############################################### GOOD ############################################### 
vector<int> countBits(int num) {
    vector<int> result;
    int idx = 1;
    int offset = 1;
    result.push_back(0);
    while(idx <= num) {
        if(offset*2 == idx) {
           offset = offset*2;
        }
        int tmpR = result[idx - offset] + 1;
        //cout << "idx = " << idx << " offset = "<< offset << " result = " << result[idx] << "\n" ;
        result.push_back(tmpR);
        idx+=1;
    }
    return result;
}
//O(n*sizeof(integer))
//############################################### Ugly  ############################################### 
vector<int> countBits(int num) {
    vector<int> result;
    int idx = 1;
    result.push_back(0);
    while(idx <= num) {
        int cnt = 0;
        int tmp = idx;
        while(tmp > 0) {
            //cout << tmp << endl;
            tmp = tmp & (tmp-1);
            cnt = cnt + 1;
        }
        result.push_back(cnt);
        idx+=1;
    }
    return result;
}
int main() {
  countBits(5);
  cout << endl;
}
