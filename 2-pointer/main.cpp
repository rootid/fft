#include "intersection.cpp"

int main() {

  Solution s;
  int a[] = {1 ,2 ,3};
  int b[] = {1 ,2 ,3};
  vector<int> av(a,a+sizeof(a)/sizeof(a[0]));
  vector<int> bv(b,b+sizeof(b)/sizeof(b[0]));
  vector<int> result;
  result = s.intersection(av,bv);
  for(int i=0;i<result.size();i++) {
    cout << result[i] << " \t " ;
  }
  cout << endl;

}
