//Write a program to find the n-th ugly number.
//Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.
//For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10
//ugly numbers.
//Note that 1 is typically treated as an ugly number.
//Hint:
//The naive approach is to call isUgly for every number until you reach the nth
//one. Most numbers are not ugly. Try to focus your effort on generating only
//the ugly ones.
//An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly
//number.
//The key is how to maintain the order of the ugly numbers. Try a similar
//approach of merging from three sorted lists: L1, L2, and L3.
//Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 *
//3, L3 * 5).

#include "../headers/global.hpp"

//We have an array k of first n ugly number. We only know, at the beginning,
//the first one, which is 1. Then
//
//k[1] = min( k[0]x2, k[0]x3, k[0]x5). The answer is k[0]x2. So we move 2's
//pointer to 1. Then we test:
//
//k[2] = min( k[1]x2, k[0]x3, k[0]x5). And so on. Be careful about the cases
//such as 6, in which we need to forward both pointers of 2 and 3.

///################# Evertime iterate over the index variables to find the min ugly #################
int nthUglyNumber(int n){
	int i2=0, i3=0, i5=0;
  vector<int> ugly(n,INT_MAX);
	ugly[0] = 1;
	for (int i=1; i<n; i++) {
		ugly[i] = min(ugly[i2]*2, min(ugly[i3]*3, ugly[i5]*5) );
		if (ugly[i]%2 == 0)
      i2++;
		if (ugly[i]%3 == 0)
      i3++;
		if (ugly[i]%5 == 0)
      i5++;
	}

	return ugly[n-1];
}

int nthUglyNumber(int n) {
       if(n <= 0) return false; // get rid of corner cases
       if(n == 1) return true; // base case
       int t2 = 0, t3 = 0, t5 = 0; //pointers for 2, 3, 5
       vector<int> k(n);
       k[0] = 1;
       for(int i  = 1; i < n ; i ++) {
           k[i] = min(k[t2]*2,min(k[t3]*3,k[t5]*5));
           if(k[i] == k[t2]*2)  {
             t2++;
           }
           if(k[i] == k[t3]*3) {
             t3++;
           }
           if(k[i] == k[t5]*5) {
             t5++;
           }
       }
       return k[n-1];
}



int nthUglyNumber(int n) {
     if (n == 1)
         return 1;
     vector<int> v2(n, 0), v3(n, 0), v5(n, 0);
     v2[0] = 2;
     v3[0] = 3;
     v5[0] = 5;
     int a = 0, b = 0, c = 0;
     int count = 1, ret = 0, i = 1;
     while (count != n) {
         ret = min(v2[a], min(v3[b], v5[c]));
         v2[i] = 2 * ret;
         v3[i] = 3 * ret;
         v5[i] = 5 * ret;
         if (v2[a] == ret) {
             ++a;
         }
         if (v3[b] == ret) {
             ++b;
         }
         if (v5[c] == ret) {
             ++c;
         }
         ++i;
         ++count;
     }
     return ret;
}

int nthUglyNumber(int n) {
		queue<int> twoQue, threeQue, fiveQue;
		int cur = 1;
		while (--n)
		{
			int c;
			do
			{
				twoQue.push(cur * 2);
				threeQue.push(cur * 3);
				fiveQue.push(cur * 5);
				c = min(twoQue.front(), min(fiveQue.front(), threeQue.front()));
				if (c == twoQue.front())
					twoQue.pop();
				if (c == threeQue.front())
					threeQue.pop();
				if (c == fiveQue.front())
					fiveQue.pop();
				if (c != cur)
				{
					cur = c;
					break;
				}
			} while (c != cur);
		}
		return cur;
}
