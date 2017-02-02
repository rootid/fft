// Fizz Buzz
//Write a program that outputs the string representation of numbers from 1 to n.
//But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.
//Example:
//n = 15,
//Return:
//[
//    "1",
//    "2",
//    "Fizz",
//    "4",
//    "Buzz",
//    "Fizz",
//    "7",
//    "8",
//    "Fizz",
//    "Buzz",
//    "11",
//    "Fizz",
//    "13",
//    "14",
//    "FizzBuzz"
//]

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

vector<string> fizzBuzz(int n) {
    vector<string> res;
    // 3x : Fizz
    // 5x : Buzz
    // 15x : FizzBuzz
    stringstream ss;
    for(int i=1;i<=n;i++) {
        if (i%3 == 0) {
           ss << "Fizz"; 
        }
        if(i%5 == 0) {
           ss << "Buzz";
        } 
        if(ss.str().size() == 0) {
            ss << i;
        }
        res.push_back(ss.str());
        stringstream().swap(ss);
        //ss.str("");
        //ss.clear();
    }
    for(auto t: res) {
      cout << t << endl;
    }
    return res;
}


vector<string> fizzBuzz(int n) {
    vector<string> res;
    // 3x : Fizz
    // 5x : Buzz
    // 15x : FizzBuzz
    stringstream ss;
    for(int i=1;i<=n;i++) {
        if(i%15 == 0) {
            ss << "FizzBuzz";
        } else if ( i%3 == 0) {
           ss << "Fizz"; 
        } else if( i%5 == 0) {
           ss << "Buzz";
        } else {
            ss << i;
        }
        res.push_back(ss.str());
        stringstream().swap(ss);
        //ss.str("");
        //ss.clear();
    }
    for(auto t: res) {
      cout << t << endl;
    }
    return res;
}

int main() {
  fizzBuzz(7);
}
