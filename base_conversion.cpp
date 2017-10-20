#include<iostream>
using namespace std;

//Need to reverse the number
void getBase2Rec(int n) {
	if(n <= 1) { 
		cout << n << endl; 
		return; 
	}
	int result = n%2;
	cout << result  << ""; 
	getBase2Rec(n/2);
}

int main() {

	getBase2Rec(10);
	getBase2Rec(11);
}
