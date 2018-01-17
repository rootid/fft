//Write a program to check whether a given number is an ugly number.
//Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.
//Note that 1 is typically treated as an ugly number.

#include<iostream>
using namespace std;



//Bad
bool isUgly(int num) {

    if(num == 0) { 
      return false;
    }
    while(num%2 == 0) { 
      num/=2; 
      //cout << " 2 " << num << endl;
    }
    while(num%3 == 0) { 
      num/=3; 
      //cout << " 3 " << num << endl;
    }
    while(num%5 == 0) { 
      num/=5;
      //cout << " 5 " << num << endl;
    }
    
    return num == 1;
}

//Good
bool isUgly(int num) {
   if(num <=0 )  { 
     return false;
   }
   int factor[] ={2,3,5};
   for(int i=0; i<3;i++) {
       while(num%factor[i] == 0)  { 
         num/=factor[i];
       }
   }
   return num==1;
}

//Recursion GOOD
bool isUgly(int num) {
 if(num<=0) { 
   return false; 
 }
 if(num==1) { 
   return true;
 }
 bool two=false, three=false, five=false;
 if(num%2==0) { 
   two=isUgly(num/2); 
 }
 if(num%3==0) {
   three=isUgly(num/3);
 }
 if(num%5==0) { 
   five=isUgly(num/5);
 }
 return two||three||five;
}
int main() {

}
