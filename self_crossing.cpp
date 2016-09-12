//You are given an array x of n positive numbers. You start at point (0,0) and moves x[0] metres to the north, then x[1] metres to the west, x[2] metres to the south, x[3] metres to the east and so on. In other words, after each move your direction changes counter-clockwise.
//Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not.
//Example 1:
//Given x = [2, 1, 1, 2],
//┌───┐
//│   │
//└───┼──>
//    │
//Return true (self crossing)
//Example 2:
//Given x = [1, 2, 3, 4],
//┌──────┐
//│      │
//│
//│
//└────────────>
//Return false (not self crossing)
#include<iostream>
#include<vector>
#include<utility>
// uncomment to disable assert()
// #define NDEBUG
#include<cassert>
using namespace std;

bool isSelfCrossing(vector<int>& x) {

  vector<pair<int,int>> coOrdinates;
  int len = x.size();
  assert(len == 4);
  coOrdinates.push_back(make_pair(0,0));
  int nexty = coOrdinates[0].second + x[0];
  coOrdinates.push_back(make_pair(0,nexty));

  int nextx = coOrdinates[1].first - x[1];
  coOrdinates.push_back(make_pair(nextx,coOrdinates[1].second));

  nexty = coOrdinates[2].second - x[2];
  coOrdinates.push_back(make_pair(coOrdinates[2].first,nexty));

  nextx = coOrdinates[3].first + x[3];
  coOrdinates.push_back(make_pair(nextx,coOrdinates[3].second));

  if(coOrdinates[4].first >= 0 && coOrdinates[4].second >= 0) {
    return true;
  }
  return false;
}

int main() {

    //vector<int> t {12,3,5,6};
    vector<int> t {1,2,3,4};
    //vector<int> t {1,1,1,1};
    //vector<int> t {2,1,1,2};

    if  ( isSelfCrossing(t) == true) {
      cout << "SELF crossing" << endl;
    } else {
      cout << "NO SELF crossing" << endl;
    }
}
