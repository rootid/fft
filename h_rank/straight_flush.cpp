
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
#include <unordered_map>

using namespace std;

int getNumber (char ch) {
    
    switch(ch) {
        case 'T':
         return 10;
        case 'J' :
         return 11;
        case 'Q' :
         return 12;
        case 'K' :
         return 13;
        case 'A' :
          return 1;
    }
    //cout << "return ch " << ch << endl;
    return ch  - '0';
    
}
bool isStraightFlush(vector<string>& cards) {
    
    if (cards.size() < 5 ) {
        return false;
    }
    string cE = cards[0];
    int idxArr[5] = {-1,-1,-1,-1,-1};
    int SIZE = 5;
    //Now we call the sort function
    idxArr[0] = getNumber(cE[0]);
    char card = cE[1];
    //cout << idx << endl;    
    for (int i=1;i<cards.size();i++) {
        cE = cards[i];
        char card_ = cE[1];
        if (card != card_ ) {
            return false;
        }
        idxArr[i] = getNumber(cE[0]);
    }
    sort(idxArr, idxArr+ SIZE);
    if ( idxArr[0] == 1 && idxArr[1] == 10) {
        idxArr[0] = 14;
        sort(idxArr, idxArr+ SIZE);
    }
    for (int i=1;i<5;i++) {
      //cout << idxArr[i] << "____" << idxArr[i-1]   << endl;
      if (idxArr[i] - idxArr[i-1] != 1) {
        return false;
      }
    }
    return true;
}

int main(){
    vector<string> cards(5);
    for(int cards_i = 0;cards_i < 5;cards_i++){
       cin >> cards[cards_i];
    }
    if ( true == isStraightFlush(cards) ) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
