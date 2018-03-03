//Super Ugly Number
//Write a program to find the nth super ugly number.
//Super ugly numbers are positive numbers whose all prime factors are in the
//given prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16,
//19, 26, 28, 32] is the sequence of the first 12 super ugly numbers given
//primes = [2, 7, 13, 19] of size 4.
//Note:
//(1) 1 is a super ugly number for any given primes.
//(2) The given numbers in primes are in ascending order.
//(3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.

#include "../headers/global.hpp"

//ugly number is ugly[i] , Index[j] is the index of the smallest of all ugly
//numbers that we already constructed , such that prime[j]*ugly[index[j]]
//################ if we pick the prime # the increase the index
//[2,3,5]
//           [1,2,INT_MX]
//[0,0,0] -> [1,0,0]
int nthSuperUglyNumber(int n, vector<int> primes) {
    int len = primes.size();
    vector<int> index(len,0); //index[0]==0, ... index[len-1]==0
    vector<int> ugly(n,0);
    ugly[0] = 1;
    for(int i=1; i<n; i++) {
        int nextUgly = INT_MAX;
        for(int j=0; j<len; j++){
            nextUgly = min(ugly[index[j]]*primes[j], nextUgly);
        }
        ugly[i] = nextUgly;
        for (int j=0; j<len; j++) {
            if(ugly[i] % primes[j] ==0 ) {
              index[j]++;
            }
        }

    }
    return ugly[n-1];
}

int nthSuperUglyNumber(int n, vector<int>& primes) {
  int plen = primes.size();
  vector<int> index(plen, 0), ugly(n, INT_MAX);
  ugly[0]=1;
  //Get the nth Ugly # w/o sorting
  for(int i=1; i<n; i++) {

      for(int j=0; j<plen; j++) {
        ugly[i] = min( ugly[i], ugly[index[j]]*primes[j] );
      }
      for(int j=0; j<plen; j++)  {
        if(ugly[i] == ugly[index[j]]*primes[j] ) {
          index[j] += 1;
        }
      }
  }
  return ugly[n-1];
}


int nthSuperUglyNumber(int n, vector<int>& p) {
  int plen = p.size();
  vector<int> idx(plen,0),ugly(n,INT_MAX);;
  ugly[0] = 1; // first is 1
  for (int i = 1; i < n; i++) {
      int nextUgly = INT_MAX;
      for (int j = 0; j < plen; j++) {
          //2,5 => (2,5)
          nextUgly = min(nextUgly, primes[j] * ugly[idx[j]]);
      }
      ugly[i] = nextUgly;
      for (int j = 0; j < plen; j++) {
          if (ugly[idx[j]] * primes[j] == nextUgly) {
              idx[j]++;
              break;
          }
      }
  }
  return ugly[n - 1];
}

//multiply a previous ugly number by one of the primes in the list.
//If current ugly number is ugly[i] , Index[j] is the index of the smallest of
//all ugly numbers
//that we already constructed , such that prime[j]*ugly[index[j]]
int nthSuperUglyNumber(int n, vector<int>& p) {
    vector<int> index(p.size(),0), res(n);
    res[0]=1;
    for(int i=1;i<n;i++){
        int x = INT_MAX;
        for(int j=0;j<p.size();j++){
            x = min(x,res[index[j]]*p[j]);
        }
        for(int j=0;j<p.size();j++){
            if(x==res[index[j]]*p[j]){
                index[j]++;
                break;
            }
        }
        //modification part to handle
        //[2,5] and we are to calculate 7th ugly no. according to the code it will be 1,2,4,5,8,10,10 because 10 is both multiple of 2 & 5.
        if(res[i-1] != x)
            res[i]=x;
        else i--;
    }
    return res[n-1];
}
