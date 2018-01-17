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


//######################################### With Mod operation ######################################### 
public List<String> fizzBuzz(int n) {
    String fz = "Fizz";
    String bz = "Buzz";
    String fzBz = "FizzBuzz";
    
    List<String> fizBuzzList = new ArrayList<>();;
    for(int i=1;i<=n;i++) {
        if(i %3 == 0 && i %5 == 0) fizBuzzList.add(fzBz);
        else if(i % 3 == 0)fizBuzzList.add(fz);
        else if(i % 5 == 0) fizBuzzList.add(bz);
        else fizBuzzList.add(String.valueOf(i));
    }
    return fizBuzzList;
}
//######################################### W/o Mod operation ######################################### 
 public List<String> fizzBuzz(int n) {
        List<String> ret = new ArrayList<String>(n);
        for(int i=1,fizz=0,buzz=0;i<=n ;i++){
            fizz++;
            buzz++;
            if(fizz==3 && buzz==5){
                ret.add("FizzBuzz");
                fizz=0;
                buzz=0;
            }else if(fizz==3){
                ret.add("Fizz");
                fizz=0;
            }else if(buzz==5){
                ret.add("Buzz");
                buzz=0;
            }else{
                ret.add(String.valueOf(i));
            }
        } 
        return ret;
    }

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
