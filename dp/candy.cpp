//Candy
//There are N children standing in a line. Each child is assigned a rating
//value.
//You are giving candies to these children subjected to the following
//requirements:
//Each child must have at least one candy.
//Children with a higher rating get more candies than their neighbors.
//What is the minimum candies you must give?
#include<iostream>
#include<vector>
using namespace std;

int candy(vector<int>& ratings) {

  int totalCandy = 0;
  unsigned int n = ratings.size();
  vector<int> result(n,0);
  result[0] = 1;

  //Left scan : For child i to make sure it has more candies than its left neighbor if it has a higher rating
  //+Keep at least 1 candy
  for(int i=1;i<n;i++) {
    if (ratings[i] > ratings[i-1]) {
      result[i] = result[i-1] + 1;
    } else {
        result[i] = 1;
    }
  }

  //Right Scan : For child i to make sure it has more candies than its right neighbor if it has a higher rating
  for(int i=n-2;i>=0 ;i--) {
    if (ratings[i] > ratings[i+1]) {
         result[i] = max(result[i],result[i+1]+1);
    }
  }
  //for(int i=n-2;i>=0 ;i--) {
  //  if (ratings[i] > ratings[i+1] result[i] < (result[i+1]+1) ) {
  //  }
  //}
  for(unsigned int i=0;i<n ;i++) {
    totalCandy += result[i];
  }
  //cout << "total candy = " << totalCandy << endl;
  return totalCandy;
}

int main() {
  int a[] = {1,3,3,3,2};
  vector<int> av(a,a+sizeof(a)/sizeof(a[0]));
  candy(av);
}
