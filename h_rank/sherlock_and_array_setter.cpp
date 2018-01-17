
// https://www.hackerrank.com/challenges/sherlock-and-array/editorial
#include<bits/stdc++.h>
using namespace std;
#define assn(n,a,b) assert(n<=b && n>=a)
typedef long long LL;
LL pre[100005];
int main()
{
    int t;
    cin >> t;
    assn(t,1,10);
    while(t--)
    {
        LL n,i,j,flag=0,x;
        cin >> n;
        assn(n,1,100000);
        for(i=1; i<=n; i++)
        {
            cin >> x;
            assn(x,1,20000);
            // store pre[i]= sum of all elements till index i.
            pre[i]=pre[i-1]+x;
        }
        for(i=1; i<=n; i++)
        {
            // check if sum to left is same as sum to right
            if(pre[i-1]==(pre[n]-pre[i]))flag=1;
        }
        if(flag)cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
