//Compare two version numbers version1 and version2.
//If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.
//You may assume that the version strings are non-empty and contain only digits and the . character.
//The . character does not represent a decimal point and is used to separate number sequences.
//For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.
//Here is an example of version numbers ordering:
//0.1 < 1.1 < 1.2 < 13.37
#include "../headers/global.hpp"
int compareVersion(string version1, string version2) { 
  while( !(version1.empty() && version2.empty()) ) {
			size_t idx1 = 0;
			size_t idx2 = 0;
      int v1 = version1.empty() ? 0 : stoi(version1, &idx1);
      int v2 = version2.empty() ? 0 : stoi(version2, &idx2);
			version1.erase(0, idx1+1);
			version2.erase(0, idx2+1);
      if (v1 > v2) {
          return 1;
      }
      else if (v1 < v2) {
          return -1;
      } 
  } 
  return 0;
}

//FIX ME eg. 1.2323423 < 1.3
//NOTE : Create weighted sum in decreasing order
int  getNumbers(string& version,char delim) {
    stringstream ss(version);
    string item;
    vector<int> elems;
    double idx = 1;
    int res = 0;
    while (std::getline(ss, item, delim)) {
      res += (int) (idx * stoi(item));
      idx = (double) idx/ (double) 2;
    }
    return res;
}

int compareVersion(string version1, string version2) {
    char delim = '.';
    int v1 = getNumbers(version1,delim);
    int v2 = getNumbers(version2,delim);
    if(v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    }
    return 0;
}

int main() {
  compareVersion("1.02","1.02");
}
