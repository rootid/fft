
//https://www.hackerrank.com/challenges/utopian-tree/editorial


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int fastexp(int a,int n){
    if (n==1) return a;
    if (n%2==0) return (fastexp(a,n/2)*fastexp(a,n/2));
    else return (a*fastexp(a,(n-1)/2)*fastexp(a,(n-1)/2));
}
int main() {
    int t;
    int n,i;
    scanf("%d",&t);
    for (i=0;i<t;i++) {
        scanf("%d",&n);
        printf("%d\n",fastexp(2,(n+1)/2+1)-1-(n%2));
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}



#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int getHeight(int n) {
    int ht = 1;
    
    if (n == 0) {
        return ht;
    } else if (n%2 == 0) {
        return ht + 1 + getHeight(n -1);
    } else {   
      return 2*ht + getHeight(n -1);
    }
}
int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        
        int r = getHeight(n);
        if (n == 0) {
            r = r;
        }
        else if (n %2 == 0) {
            r = r - 2;
        } else if (n %2 == 1) {
            r =r -1;
        }
        cout << r << endl;
    }
    
    
    
    return 0;
}
