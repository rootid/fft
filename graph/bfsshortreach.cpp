#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

//2
//4 2
//1 2
//1 3
//1
//3 1
//2 3
//2
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int no_of_test_case;
    cin >> no_of_test_case;
	
    for(int i=0;i<no_of_test_case;i++) {
      int edges;
	    int nodes;
      cin >> nodes;
	    cin >> edges;
	    unordered_map<int,vector<int> > g;
	    for(int i=0;i<edges;i++) {
	       int from;
	       int to;
	       cin >> from;
	       cin >> to;
         //cout << "from = " << from << " | to = " << to << endl;
	       g[from].push_back(to);
	    }
	    int target;
	    cin >> target;
      //cout << "target = " << target << endl;
      vector<int> result(nodes+1,-1);
	    if (g.find(target) != g.end()) {
	    	vector<int>	vecList = g[target];
        sort(vecList.begin(),vecList.end());
        for (int i=0;i<vecList.size();i++) {
          //cout << vecList[i] << " ";
          result[vecList[i]] = 6;
        }
	    } 

      for (int i=1;i<=nodes;i++) {
        if (i == target) {
          continue;
        }
        cout << result[i] << " ";
      }
      cout << endl;
    }
    return 0;
}
