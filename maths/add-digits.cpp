#include<iostream>
using namespace std;



///https://en.wikipedia.org/wiki/Digital_root#Congruence_formula

public int addDigits(int num) {
    int base = 10;
    return 1 + (num - 1) % (base - 1);
}

int addDigits(int num) {
   if(num < 9) {
        return num;
   }
   return addDigits(num/10 + num%10) ;
}

int addDigits1(int num) {
   
    while(num > 9) {
      int sum = 0;
      while(num > 0)  {
        sum += num%10;
        num = num/10;
      }
      num = sum;
   }
   return num;
}


int addDigits(int num) {
     return 1 + (num - 1) % 9;
 }

//Confused + wrong iteration
//int addDigits(int num) {
//    if(num < 9) {
//        return num;
//   }
//   num =  ( (num%10) + addDigits(num / 10) );
//   return num;
//}


int main () {
  //int result = addDigits(345);
  int result = addDigits1(345);
  cout << "result = " << result  << endl;
}
