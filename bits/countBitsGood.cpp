//Counting Bits
//O(n) + DP + Pattern-matching
#include<iostream>
#include<vector>
using namespace std;


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

int main() {

  countBits(5);
  cout << endl;
}
