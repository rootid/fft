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

#include "../headers/global.hpp"

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

//######################### Good #####################
vector<vector<int> > generate(int numRows) {
    vector<vector<int>> r(numRows);

    for (int i = 0; i < numRows; i++) {
        r[i].resize(i + 1);
        r[i][0] = r[i][i] = 1;
        for (int j = 1; j < i; j++)
            r[i][j] = r[i - 1][j - 1] + r[i - 1][j];
    }
    return r;
}

//######################### Ugly #####################
vector<vector<int> > generate(int numRows) {
  vector<vector<int> > result;
  if(numRows ==0) {
      return result;
  }
  result.resize(numRows);
  result[0].push_back(1);
  int cnt = 2;
  for(int j=1;j<numRows;j++) {
    result[j].resize(cnt);
    for(int k=0;k<cnt;k++) {
        result[j][k] = 1;
        if(k < j) {
          result[j][k] = result[j-1][k-1] + result[j-1][k];
        } else {
        }
    }
    cnt += 1;
  }
  return result;
}

//################### DEBUG #####################
void print_vec(vector< vector<int> >& v) {
  for(int i=0;i<v.size();i++) {
    for(int j=0;j<v[i].size();j++) {
      cout << v[i][j] << "\t";
    }
    cout << endl;
  }
}

int main() {
  //vector< vector<int> > v = generate(4);
  vector< vector<int> > v = generate(5);
  print_vec(v);
}
