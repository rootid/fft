//Excel Sheet Column Title
//Given a positive integer, return its corresponding column title as appear in an Excel sheet.
//For example:
//    1 -> A
//    2 -> B
//    3 -> C
//    ...
//    26 -> Z
//    27 -> AA
//    28 -> AB 
#include<iostream>
#include<assert.h>
#include<string>
#include<algorithm>
using namespace std;

string convertToTitle(int n) {
    
    string title;
    assert(n > 0);
    while(n) {
        n = n - 1;
        int idxChar = n % 26;
        title += ('A' + idxChar);
        n = n / 26;
    }
    reverse(title.begin(),title.end());
    cout << title << endl;
    return title;
}
int main() {
  convertToTitle(1); //A
  convertToTitle(27); //AA
  convertToTitle(26); //Z
  convertToTitle(28); //AB
  convertToTitle(29); //AC
  convertToTitle(-1); //A
}
