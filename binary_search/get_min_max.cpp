#include "../headers/global.hpp"
//Find the largest and smallest number in a list. The list is stored as two
//sections, one in ascending order and the other in descending order.
//input [ 2 3 4 5 6 7 10 9 8 7]  //simple : O(n) possibilities: 1.
//[mn1,mx1,mx2,mn2]
//smallest : 2                                                  2.
//[mx1,mn1,mn2,mx2]
//Largest 10
//input [ 99 98 97 96 1 2 3 4 5 6 ]  // sm = 1,lar = 99
//99,6 -> 97,96,1,2
//1ele,2 elements,3,4
//input [100 101 103 4 3 2 1]
int binaryPart(vector<int>& );
vector<int> getMinMax(vector<int>& a) {
  //for case 1
  int sz = a.size();
  int min_ = min(a[0],a[sz - 1]);
  int mid = binaryPart(a);
  cout << a[mid] << endl;
  int max_ = max(a[mid],a[mid-1]);
  vector<int> min_max({min_,max_});

  cout << "min = " << min_max[0] << "| max = " << min_max[1] << endl;
  return min_max;
}

int binaryPart(vector<int>& a) {
  int l = 0;
  int h = a.size();
  while(l < h) {
    int mid = l + (h-l)/2;
    if(a[mid-1] < a[mid] && a[mid] < a[mid+1]) {
      l = mid+1;
    } else if(a[mid-1] > a[mid] && a[mid] > a[mid+1]) {
      h = mid;
    } else {
      return mid;
    }
  }
  return l;
}


int main() {
  vector<int> av( {2,3,4,5,6,7,10,9,8,7} );
  getMinMax(av);
}
