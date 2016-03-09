#include<iostream>
using namespace std;

int compareVersionUtils(string v1,string v2) {

  if(v1.length() == v2.length()) {
    for (int i=0;i<v1.length();i++) {
        if (v1[i] - v2[i] > 0 ) {
            return 1;
        } else if (v1[i] - v2[i] < 0 ) {
          return -1;
        } 
    }
    return 0;
  } else if (v1.length() > v2.length()) {
    return 1; 
  } else {
    return -1; 
  }

}

void splitString(string v,string &a,string &b) {

  int idx = 0;
  int startIdx = 0;
  while(v[startIdx] == '0') {
    startIdx += 1;
  }
  while(v[idx] != '.' && idx < v.length()) {
    idx += 1;
  }
  a = v.substr(startIdx,idx);
  if (idx < v.length()) {
     b = v.substr(idx+1);
  }
}


int compareVersion(string version1, string version2) {  

  string v1 = "";
  string v1R = "";
  splitString(version1,v1,v1R);

  string v2 = "";
  string v2R = "";
  splitString(version2,v2,v2R);

  cout << " v1 = " << v1 << " | v1R =  " << v1R << endl;
  cout << " v2 = " << v2 << " | v2R =  " << v2R << endl;
  int result = compareVersionUtils(v1,v2);
  if( 0 == result ) {
    cout << "left halfs are equal" << endl;
    return compareVersionUtils(v1R,v2R);
  }

  cout << "left halfs are not equal" << endl;
  return result;
  
}

int compareVersionWrapper() {

}

int main() {
    
  string version1 = "1";
  string version2 = "01";

  compareVersion(version1,version2);
}
