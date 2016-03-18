//Counting Bits
//O(n*sizeof(integer))
#include<iostream>
#include<vector>
using namespace std;


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

  countBits(2);
}
