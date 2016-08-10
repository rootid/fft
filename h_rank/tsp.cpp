
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int m;
    int n;
    int c;
    cin >> m;
    cin >> n;
    cin >> c;
 
    int u_c = (m-c) + (n-c) + c;
    u_c -= 1;
    
    unsigned int result =1;
     for( int i = 1; i <= u_c; ++i)
        result *= i;

    cout << result << endl; 
    return result;
    
 
}
