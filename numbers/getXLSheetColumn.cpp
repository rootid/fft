//Excel Sheet Column Number
#include<iostream>
#include<string>
using namespace std;


string getXLSheetColumn (int idx) {

    string result = "";
    int MAX_BASE = 26;
    char CHAR_BASE = 'A';
    int remainder = 0;
    while (idx > 0) {
        remainder = idx % MAX_BASE ;
        //cout << idx << endl;
        idx = idx / MAX_BASE ;
        remainder--;
        result.push_back ( CHAR_BASE + remainder);
    }
    reverse(result.begin(),result.end();
    return result;
}

int main() {

  getXLSheetColumn (28);
}
