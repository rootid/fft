//Candy
//There are N children standing in a line. Each child is assigned a rating value.
//You are giving candies to these children subjected to the following requirements:
//Each child must have at least one candy.
//Children with a higher rating get more candies than their neighbors.
//What is the minimum candies you must give?
#include<iostream>
#include<vector>
using namespace std;

int candy(vector<int>& ratings) {

  int totalCandy = 0;
  int preVCandy = 1;
  int nextCandy = 1;
  unsigned int n = ratings.size();
  vector<int> result(n,1);
  for(int i=1;i<n;i++) {
    if (ratings[i] > ratings[i-1]) {
      result[i] += 1;
    } 
    //cout << "i = " << i << " R =" << result[i] << " RATI=" << ratings[i]  << endl;
  }
  //cout << ">>>>>>>>>>>>>" << endl;
  for(int i=n-2;i>=0 ;i--) {
    if (ratings[i] > ratings[i+1]) {
        result[i] = max(1+result[i+1],result[i]);
    }
    //cout << "i = " << i << " R =" << result[i] << " RATI=" << ratings[i]  << endl;
  }

  //cout << "TC  = " << totalCandy << endl;
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
