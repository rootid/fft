
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;


int main(){
    string s;
    cin >> s;
    int count = 0;
    for(int i=0;i<s.length();i++) {
        int char_ = s[i] - 'A';
        if(char_ <= 26 && char_ >= 0) {
            count +=1 ;
        }
    }
    cout << count << endl;
    return count;
}
