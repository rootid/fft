//HEAD: Given a random string S and another string T with unique elements, find
//the minimum consecutive sub-string of S such that it contains all the
//elements in T. example: S='adobecodebanc' T='abc'  answer='banc'

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
using namespace std;


string getMinSubStr(string &s,string &t) {

  unordered_map<char, int> u_map;
  vector< vector<int> > index_store;
  for (int i=0;i<t.length();i++) {
      u_map[t[i]] = i;
  }

  for (int i=0;i<s.length();i++) {
    if ( u_map.find(s[i]) ) {
        index_store[u_map[s[i]]].push_back(i);
    }
  }
  int total_vtx = t.length();
  int total_path = index_store[0].size();

  //for (int i=0;i<total_path ;i++) {
  //  int distance_ = INT_MAX;
  //  for (int j=1;j<total_vtx;j++) {
  //     for (int k=0;k<index_store[j].size();k++) {
  //          = index_store[j][k];
  //      }
  //  }
  //}

}

int main() {
    cout << "Hello world" << endl;

    string s = "adobecodebanc";
    string t = "banc";
    string result = getMinSubStr (s,t);
    cout << "result = " << result << endl;

}


