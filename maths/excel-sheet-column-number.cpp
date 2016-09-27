//Excel Sheet Column Number
//Related to question Excel Sheet Column Title
//Given a column title as appear in an Excel sheet, return its corresponding column number.
//For example:
//    A -> 1
//    B -> 2
//    C -> 3
//    ...
//    Z -> 26
//    AA -> 27
//    AB -> 28 

#include<iostream>
#include<math.h>
using namespace std;
int titleToNumber(string s) {
    int len = s.size();
    int no = 0;
    //for(int i=len-1;i>=0;i--){
    //    int tmp_ = pow(26,len-i-1) * (s[i] - 'A' + 1);
    //    no += tmp_;
    //}

    for(int i=len;i>=0;i--){
        int tmp_ = pow(26,len-i) * (s[i - 1] - 'A' + 1);
        no += tmp_;
    }

    int result = 0;
    for (int i = 0; i < s.size();  i++) {
        cout <<  "B4 = " << result << endl;
        result = result * 26 + (s.at(i) - 'A' + 1);
        cout <<  "After = " << result << endl;
    }
    return no;
}

int main() {
  //int no_ = titleToNumber("AB");
  int no_ = titleToNumber("ABC");
  cout << "NO = " << no_ << endl;
}
