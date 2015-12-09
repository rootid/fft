//https://www.hackerrank.com/challenges/sherlock-and-array
//Problem Statement
//
//Русский \| 中文
//Watson gives Sherlock an array A of length N. Then he asks him to determine if there exists an element in the array such that the sum of the elements on its left is equal to the sum of the elements on its right. If there are no elements to the left/right, then the sum is considered to be zero. 
//Formally, find an i, such that, A1+A2...Ai-1 =Ai+1+Ai+2...AN.
//
//Input Format 
//The first line contains T, the number of test cases. For each test case, the first line contains N, the number of elements in the array A. The second line for each test case contains N space-separated integers, denoting the array A.
//
//Output Format 
//For each test case print YES if there exists an element in the array, such that the sum of the elements on its left is equal to the sum of the elements on its right; otherwise print NO.
//
//Constraints 
//1≤T≤10 
//1≤N≤105 
//1≤Ai ≤2×104 
//1≤i≤N
//Sample Input
//
//2
//3
//1 2 3
//4
//1 2 3 3
//Sample Output
//
//NO
//YES
//Explanation 
//For the first test case, no such index exists. 
//For the second test case, A[1]+A[2]=A[4], therefore index 3 satisfies the given conditions.

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;


int sherlock_and_array(vector <int>& a) {
        
    int len = a.size();

    vector<int> left;
    vector<int> right;

    int ans_ = 0;
    for (int i=0;i<len;i++) {
      ans_ += a[i];
      //cout << ans_ << " " ;
      left.push_back(ans_);
    }
    //cout << endl;

    ans_ = 0;
    for (int i=len-1;i>=0;i--) {
      ans_ += a[i];
      //cout << ans_ << " " ;
      right.push_back(ans_);
    }
    reverse(right.begin(),right.end());
    //cout << endl;

    for (int i=1;i<len-1;i++) {
      if (left[i-1] == right[i+1]) {
          return i;
      }
    }

   return 0;
}

int main() {
    int no_of_test_case;
    cin >> no_of_test_case;
    int _a_size;
    vector<int> _a;
    vector<int> r_v;

    for (int i=0;i<no_of_test_case;i++) {
        _a.clear();
        cin >> _a_size;
        int _a_item;
        for(int _a_i=0; _a_i<_a_size; _a_i++) {
            cin >> _a_item;
            _a.push_back(_a_item);
        }
        r_v.push_back(sherlock_and_array(_a) );
    }

    for (int i=0;i<no_of_test_case;i++) {
      if (r_v[i] == 0) {
        cout << "NO" << endl;
      } else {
        cout << "YES" << endl;
      }
    }
    return 0;
}
