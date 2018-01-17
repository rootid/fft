#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


 //8
 //1 1 2 2 6 9 9 15
 //4
 //1
 //4
 //9
 //15
//lower_bound
//binary_search
void getResult(vector<int>&db , vector<int>&q_db) {

  for(int i=0;i<q_db.size();i++) {
    for(int j=0;j<db.size();j++) {
      if(db[j] == q_db[i]) {
        cout << "Yes " << j+1 << endl;
        break;
      } else if(db[j] > q_db[i]) {
        cout << "No " << j+1 << endl;
        break;
      }
    }
  }
}

int main() {

    int _l;
    cin >> _l;
   
    vector<int> db;
    vector<int> q_db;
   
    for(int i=0;i<_l;i++) {
      int tmp;
      cin >> tmp;
      db.push_back(tmp);
    }

    int _ql;
    cin >> _ql;

    for(int i=0;i<_ql;i++) {
      int t;
      cin >> t;
      q_db.push_back(t);
    }
    getResult(db,q_db);
    return 0;
}
