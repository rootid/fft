//Given numRows, generate the first numRows of Pascal's triangle.
//For example, given numRows = 5,
//Return
//[
//     [1],
//    [1,1],
//   [1,2,1],
//  [1,3,3,1],
// [1,4,6,4,1]
//]

#include<iostream>
#include<vector>
using namespace std;

vector<vector<int> > generate(int numRows) {
  vector<vector<int> > result;
  result.resize(numRows);
  result[0].push_back(0);
  for(int i=1;i<numRows;i++) {
    for(int j=1;j<i-1;j++) {
      result[i].resize(1);
      result[i][j] = result[i-1][j]+result[i-1][j-1];
    }
    result[i].resize(1);
    result[i][i] = 1;
  }
  return result;
}

int main() {
}
