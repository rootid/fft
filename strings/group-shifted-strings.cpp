//Group Shifted Strings
//Given a string, we can "shift" each of its letter to its successive letter,
//for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:
//"abc" -> "bcd" -> ... -> "xyz"
//Given a list of strings which contains only lowercase alphabets, group all
//strings that belong to the same shifting sequence.
//For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
//A solution is:
//[
//  ["abc","bcd","xyz"],
//  ["az","ba"],
//  ["acef"],
//  ["a","z"]
//]

#include "../headers/global.hpp"

string shift(string& s) {
    string t;
    int n = s.length();
    for (int i = 1; i < n; i++) {
        int diff = s[i] - s[i - 1];
        if (diff < 0) {  //To tackle the cases like "az","ba"
          diff += 26;
        }
        //t += 'a' + to_string(diff) + ','; // cases like "ach","az" both will
        //produce unique string
        t += 'a' + (diff) + ',';  //converts "t" into unique white space string

    }
    cout <<  "s = " << s << " t = " << t << endl;
    //char * S = new char[t.length() + 1];
    //strcpy(S,t.c_str());
    //printf(" %s --> ",S);
    return t;
}
vector<vector<string> > groupStrings(vector<string>& strings) {
    unordered_map<string, vector<string> > mp;
    for (string  s : strings) {
        mp[shift(s)].push_back(s);
    }
    vector<vector<string> > groups;
    for (auto m : mp) {
        vector<string> group = m.second;
        sort(group.begin(), group.end());
        groups.push_back(group);
    }
    return groups;
}


int main() {
  vector<string> stv({"abc", "bcd", "acef", "xyz", "az", "ba", "a", "z","ach"});
  //cout << 'h'  - 'c' << endl;
  //cout << 'c'  - 'a' << endl;
  string t1;
  t1 += 'a' + 12 + 'b';
  cout << "T1 " << t1 << endl;
  groupStrings(stv);
}
