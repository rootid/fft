
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

int getDiagonalDiff(vector< vector<int> > a) {

  int priSum = 0;
  int secSum = 0;
  int result =0 ;
  int n = a.size();
  for (int i=0,j=0;i<n;i++,j++) {
      priSum += a[i][j];
  }

  for (int i=0,j=n-1;i<n;i++,j--) {
    secSum += a[i][j];
  }
  result = abs(priSum - secSum);

  return result;
}

int main(){
    int n;
    cin >> n;
    vector< vector<int> > a(n,vector<int>(n));
    for(int a_i = 0;a_i < n;a_i++){
       for(int a_j = 0;a_j < n;a_j++){
          cin >> a[a_i][a_j];
       }
    }
    int result_ = getDiagonalDiff(a);
    cout <<   result_  << endl;
    return 0;
}


//property of non-diagonal elements i+j = n-1
//#include <iostream>
//
//using namespace std;
//
//int main(int argc, const char * argv[])
//{
//    int n;
//    cin>>n;
//
//    int a[n][n];
//
//    long long d1=0; //First Diagonal
//    long long d2=0; //Second Diagonal
//
//    for(int i=0;i<n;i++)
//    {
//        for(int j=0;j<n;j++)
//        {
//            cin>>a[i][j];
//            if(i==j)
//                d1+=a[i][j];
//            if(i==n-j-1)  // property of non-diagonal elements i+j = n-1
//                d2+=a[i][j];
//        }
//    }
//
//    cout<<abs(d1-d2)<<endl; //Absolute difference of the sums across the diagonals
//}
