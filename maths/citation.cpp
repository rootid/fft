#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int hIndex(vector<int>& citations) {
    int n = citations.size();
    vector<int> v(n + 1, 0);

    for(int i = 0; i < n; ++i) {
        if (citations[i] >= n) v[n]++;
        else v[citations[i]]++;
    }

    if (v[n] >= n) return n;

    for (int i = n - 1; i >= 0; i--) {
        v[i] += v[i+1];
        if (v[i] >= i) return i;
    }

    return 0;
}

int main () {

  //int cite_ [] = {3,0,6,1,5};
  int cite_ [] = {1,90};
  vector<int> vc_(cite_,cite_+sizeof(cite_)/sizeof(cite_[0]));
  int idx = hIndex(vc_);
  cout << "H-idx = " << idx << endl;

}

