#include<iostream>
#include<vector>
using namespace std;

void  printBulb(vector<int>& bulbs) {
  for(int i=0;i<bulbs.size();i++) {
    cout << bulbs[i] << "\t";
  }
  cout << endl;
}

int countOnBulbs(int bulbs[],int n) {
  int count = 0;
  for(int i=1;i<n;i++) {
    count += bulbs[i] == 1 ? 1 : 0;
  }
  return count;
}

void bulbSwitch(int n) {
  //vector<int> bulbs(n+1,1);
  int bulbs[n+1];
  bulbs[0] = -1;
  for(int i=1;i<=n;i++) {
    bulbs[i] = 1;
  }
  for(int i=2;i<n;i++) {
    //printBulb(bulbs);
    int j = 0;
    while(j<=n) {
      j += i;
      bulbs[j] = 1 - bulbs[j];
    }
    //printBulb(bulbs);
  }
 bulbs[n] = 1 - bulbs[n];

 int r = countOnBulbs(bulbs,n+1);
 cout << "RESULT " << r << endl;
 //printBulb(bulbs);
 //return r;
}

int main() {
  //bulbSwitch(4);
  //bulbSwitch(9);
  bulbSwitch(11);
  bulbSwitch(12);
  bulbSwitch(24);
  //int r = bulbSwitch(11);
  //cout << "RESULT " << r << endl;
  //bulbSwitch(10);
}
