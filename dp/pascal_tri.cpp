

#include<iostream>
#include<vector>
using namespace std;

//BETTER
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
