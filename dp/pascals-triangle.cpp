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



//################### Python #####################
class Solution(object):
    def generate(self, numRows):
        """
        :type numRows: int
        :rtype: List[List[int]]
        """        
        res = [[1]]
        for i in range(1, numRows):
            res.append(map(lambda x,y: x+y, [0]+res[-1], res[-1]+[0]))
        return res if numRows else []

//################### Python #####################
class Solution(object):
    def generate(self, numRows):
        """
        :type numRows: int
        :rtype: List[List[int]]
        if numRows = 5
               [
                     [1],
                    [1,1],
                   [1,2,1],
                  [1,3,3,1],
                 [1,4,6,4,1]
               ]
        """
        num = [[1], [1, 1]]
        if numRows == 1:
            return num[0]
        elif numRows == 2:
            return num
        elif numRows == 0:
            return []
        row = []
        for i in range(2, numRows):
            for j in range(i - 1):
                row.append(sum(num[-1][j:j + 2]))
            num.append([1] + row + [1])
            row = []
        return num

//################### Python With Map #####################
def generate(self, numRows):
        res = [[1]]
        for i in range(1, numRows):
            res += [map(lambda x, y: x+y, res[-1] + [0], [0] + res[-1])]
        return res[:numRows]
//Any row can be constructed using the offset sum of the previous row
 //   1 3 3 1 0 
 //+  0 1 3 3 1
 //=  1 4 6 4 1

//################### Python With range #####################
def triangle(n):
	result, pend = [], [1]
	for i in xrange(n):
		result.append(pend)
		pend = [1] + [pend[k] + pend[k+1] for k in xrange(len(pend) - 1)] + [1]
	return result


//################### cPP #####################
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
