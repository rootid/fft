//Count Primes
//Count the number of prime numbers less than a non-negative number, n.

#include<iostream>
using namespace std;

bool isPrime(int n) {
  if(n <= 1) {
    return false;
  }
  for(int i=2;i * i <n;i++) {
    if(n%i == 0) {
      return false;
    }
  }
  return true;
}

int countPrimes(int n) {

  int count = 0;
  for(int i=0;i<n;i++) {
    if(isPrime(i)) {
      count += 1;
    }
  }
  return count;
}


int countPrimes(int n) {

  int count = 0;
  bool isPrime[n];

  for(int i=0;i<n;i++) {
    isPrime[i] = true;
  }
  for(int i=2;i*i <n;i++) {
    if(isPrime[i] == false) {
      continue;
    }
    for(int j=i*i;j <n;j+=i) {
      isPrime[j] = false;
    }
  }
  for(int i=2;i<n;i++) {
    if(isPrime[i] == true) {
      count++;
    }
  }
  return count;
}

int main(int argc, char *argv[])
{
  
  return 0;
}
